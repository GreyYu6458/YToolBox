#ifndef _SERIALCOMMMODULE_HPP_
#define _SERIALCOMMMODULE_HPP_
#include <iostream>
#include <boost/asio/io_service.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/bind/bind.hpp>
#include <thread>
#include "common/module/BasicModule.h"
#include "common/interface/OutputInterface.hpp"

class SerialCommModule : public BasicModule {
private:
	OutputInterface<const char*, size_t> raw_bytes_oi;
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

	virtual bool activate();

	virtual bool deactivate();

	virtual std::string get_moduleName();


private:
	void set_baud_rate(int baud_rate);

	void set_parity(parity::type parity);

	void set_flow_control(flow_control::type flow_control);

	void set_stop_bits(stop_bits::type stop_bits);

	void set_charactor_size(unsigned int charactor_size);

	void set_port(const std::string& port);

	bool is_open();

	SerialCommModule();

	~SerialCommModule();
private:
	void read();

	void close();

	void set_error_status(bool e);

	bool error_status();

	void read_end(const boost::system::error_code& error, size_t bytes_transferred);

	std::string port;
	bool _is_open = false;
	bool _error = false;

	std::thread background_thread;

	static const int read_buffer_size = 512;

	char read_buffer[read_buffer_size]{ 0 };

	mutable std::mutex error_mutex;

	boost::asio::io_service* _is{ nullptr };
	boost::asio::serial_port* _sp{ nullptr };

	using boost_serial = boost::asio::serial_port;

	int _baud_rate{ 9600 };
	boost_serial::parity::type _parity{ boost_serial::parity::none };
	boost_serial::flow_control::type _flow_control{ boost_serial::flow_control::none };
	boost_serial::stop_bits::type _stop_bits{ boost_serial::stop_bits::one };
	unsigned int _charactor_size{ 8 };

	std::vector<std::string> _type_name{"string", "int", "int" , "int" , "int" };
};

// DEFINE_DYN_MODULE(SerialCommModule)

#endif