#include "SerialCommModule.h"



void SerialCommModule::set_baud_rate(int baud_rate) {
	this->_baud_rate = baud_rate;
}

void SerialCommModule::set_parity(parity::type parity) {
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

void SerialCommModule::set_flow_control(flow_control::type flow_control) {
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

void SerialCommModule::set_stop_bits(stop_bits::type stop_bits) {
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

void SerialCommModule::set_charactor_size(unsigned int charactor_size) {
	this->_charactor_size = charactor_size;
}

void SerialCommModule::set_port(const std::string& port) {
	this->port = port;
}

bool SerialCommModule::is_open() {
	return _is_open;
}

bool SerialCommModule::activate() {
	if (port.size() == 0) {
		_is_open = false;
		return false;
	}
	try {
		_sp->open(port);
		_sp->set_option(boost_serial::parity(_parity));
		_sp->set_option(boost_serial::character_size(_charactor_size));
		_sp->set_option(boost_serial::stop_bits(_stop_bits));
		_sp->set_option(boost_serial::flow_control(_flow_control));
		_sp->set_option(boost_serial::baud_rate(_baud_rate));

		_is->post(boost::bind(&SerialCommModule::read, this));

		std::thread t(boost::bind(&boost::asio::io_service::run, _is));

		background_thread.swap(t);
		_is_open = true;
		return true;
	}
	catch (boost::system::system_error& err) {
		std::cout << err.what() << std::endl;
		_is_open = false;
		return false;
	}
}

bool SerialCommModule::deactivate() {
	if (!is_open()) return true;
	_is->post(boost::bind(&SerialCommModule::close, this));
	background_thread.join();
	_is_open = false;
	_is->reset();
	if (error_status())
	{
		throw(boost::system::system_error(boost::system::error_code(),
			"Error while closing the device"));
	}
	return true;
}

std::string SerialCommModule::get_moduleName() {
	return "SerialCommModule";
}

SerialCommModule::SerialCommModule(){
	_is = new boost::asio::io_service();
	_sp = new boost::asio::serial_port(*_is);
	add_interface("raw_bytes_oi", &raw_bytes_oi);
};

SerialCommModule::~SerialCommModule() {
	deactivate();
	if (_is != nullptr)
		delete _is;
	if (_sp != nullptr)
		delete _sp;
}

void SerialCommModule::read() {
	_sp->async_read_some(boost::asio::buffer(read_buffer, read_buffer_size),
		boost::bind(&SerialCommModule::read_end,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred)
	);
}

void SerialCommModule::close()
{
	boost::system::error_code ec;
	_sp->cancel(ec);
	if (ec) set_error_status(true);
	_sp->close(ec);
	if (ec) set_error_status(true);
}

void SerialCommModule::set_error_status(bool e)
{
	std::lock_guard<std::mutex> l(error_mutex);
	_error = e;
}

bool SerialCommModule::error_status()
{
	std::lock_guard<std::mutex> l(error_mutex);
	return _error;
}

void SerialCommModule::read_end(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (error){
		if (is_open()){
			close();
			set_error_status(true);
		}
	}
	else {
		this->raw_bytes_oi.push(read_buffer, bytes_transferred);
		read();
	}
}
