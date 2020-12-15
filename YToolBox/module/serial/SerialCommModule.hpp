#ifndef _SERIALCOMMMODULE_HPP_
#define _SERIALCOMMMODULE_HPP_
#include <iostream>
#include <boost/asio/io_service.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/bind/bind.hpp>
#include <thread>
#include "common/StaticBaseModule.hpp"

class SerialCommModule : public StaticBaseModule<SerialCommModule> {
public:
	class parity {
	public:
		enum type {
			none,
			odd,
			even
		};
	};

	class flow_control {
	public:
		enum type {
			none,
			software,
			hardware
		};
	};

	class stop_bits {
	public:
		enum type {
			one,
			onepointfive,
			two
		};
	};

	void set_baud_rate(int baud_rate) {
		this->_baud_rate = baud_rate;
	}

	void set_parity(parity::type parity) {
		switch (parity) {
		case parity::none:
			this->_parity = boost_serial::parity::none;
			break;
		case parity::even:
			this->_parity = boost_serial::parity::even;
			break;
		case parity::odd:
			this->_parity = boost_serial::parity::odd;
			break;
		}
	}

	void set_flow_control(flow_control::type flow_control) {
		switch (flow_control) {
		case flow_control::none:
			this->_flow_control = boost_serial::flow_control::none;
			break;
		case flow_control::software:
			this->_flow_control = boost_serial::flow_control::software;
			break;
		case flow_control::hardware:
			this->_flow_control = boost_serial::flow_control::hardware;
			break;
		}
	}

	void set_stop_bits(stop_bits::type stop_bits) {
		switch (stop_bits) {
		case stop_bits::one:
			this->_stop_bits = boost_serial::stop_bits::one;
			break;
		case stop_bits::onepointfive:
			this->_stop_bits = boost_serial::stop_bits::onepointfive;
			break;
		case stop_bits::two:
			this->_stop_bits = boost_serial::stop_bits::two;
			break;
		}
	}

	void set_charactor_size(unsigned int charactor_size) {
		this->_charactor_size = charactor_size;
	}

	void set_port(const char* port) {
		this->port = port;
	}

	void set_port(const std::string& port) {
		this->port = port;
	}

	bool is_open() const
	{
		return _is_open;
	}

	void stop() {
		if (!is_open()) return;

		_is_open = false;
		_is->post(boost::bind(&SerialCommModule::close, this));
		background_thread.join();
		_is->reset();
		if (error_status())
		{
			throw(boost::system::system_error(boost::system::error_code(),
				"Error while closing the device"));
		}
	}

	void execute() {
		if (port.size() == 0)
		{
			on_port_not_specified();
			_is_open = false;
			return;
		}
		try {
			_sp->open(port);
			_sp->set_option(boost_serial::parity(_parity));
			_sp->set_option(boost_serial::character_size(_charactor_size));
			_sp->set_option(boost_serial::stop_bits(_stop_bits));
			_sp->set_option(boost_serial::flow_control(_flow_control));
			_sp->set_option(boost_serial::baud_rate(_baud_rate));

			// IO 服务加入read方法
			_is->post(boost::bind(&SerialCommModule::read, this));
			// 新建一个IO线程
			std::thread t(boost::bind(&boost::asio::io_service::run, _is));
			// 生命周期交换到成员线程
			background_thread.swap(t);
			_is_open = true;
		}
		catch (boost::system::system_error& err) {
			on_port_open_failed(port, err);
			_is_open = false;
		}
	}
	
	SerialCommModule() {
		_is = new boost::asio::io_service();
		_sp = new boost::asio::serial_port(*_is);
	};

	~SerialCommModule() {
		stop();
		if (_is != nullptr)
			delete _is;
		if (_sp != nullptr)
			delete _sp;
	}

private:
	

	std::string port;
	bool _is_open = false;
	bool _error = false;

	std::thread background_thread;

	static const int read_buffer_size = 512;

	char read_buffer[read_buffer_size]{0};

	mutable std::mutex error_mutex; 

	boost::asio::io_service* _is{ nullptr };
	boost::asio::serial_port* _sp{ nullptr };

	using boost_serial = boost::asio::serial_port;

	int _baud_rate{ 9600 };
	boost_serial::parity::type _parity{ boost_serial::parity::none };
	boost_serial::flow_control::type _flow_control{ boost_serial::flow_control::none };
	boost_serial::stop_bits::type _stop_bits{ boost_serial::stop_bits::one };
	unsigned int _charactor_size{ 8 };

	void read() {
		_sp->async_read_some(boost::asio::buffer(read_buffer, read_buffer_size),
			boost::bind(&SerialCommModule::read_end,
				this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

	void close()
	{
		boost::system::error_code ec;
		_sp->cancel(ec);
		if (ec) set_error_status(true);
		_sp->close(ec);
		if (ec) set_error_status(true);
	}

	void set_error_status(bool e)
	{
		std::lock_guard<std::mutex> l(error_mutex);
		_error = e;
	}

	bool error_status() const
	{
		std::lock_guard<std::mutex> l(error_mutex);
		return _error;
	}

	void read_end(const boost::system::error_code& error,
		size_t bytes_transferred)
	{
		if (error)
		{
			if (is_open())
			{
				close();
				set_error_status(true);
			}
		}
		else {
			YModuleInvokeEventCb(on_read_cmp, read_buffer, bytes_transferred);
			read();
		}
	}

	YModuleDefineEventCb(on_read_cmp, const char*, size_t)
	YModuleDefineEventCb(on_port_not_specified, void)
	YModuleDefineEventCb(on_port_open_failed, const std::string&, boost::system::system_error&)
};
#endif