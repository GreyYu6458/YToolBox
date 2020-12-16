// YToolBox.cpp: 定义应用程序的入口点。
//
#include "common/StaticBaseModule.hpp"
#include "mavlink/MavlinkParseModule.hpp"
#include "serial/SerialCommModule.hpp"
#include <iostream>

int main()
{
	SerialCommModule serial_comm_module;
	MavlinkParseModule mavlink_parse_module(0);
	mavlink_parse_module.set_on_parsed_call_back([](const mavlink_message_t& msg, const mavlink_status_t& stat) {
			printf("Received message with ID %d\t, sequence: %d\t from component %d\t of system %d\n", msg.msgid, msg.seq, msg.compid, msg.sysid);
		}
	);

	serial_comm_module.set_port("COM3");
	serial_comm_module.set_baud_rate(921600);
	serial_comm_module.set_on_read_cmp_call_back([&mavlink_parse_module](const char* c, size_t count) {
			invokeModule(mavlink_parse_module, c, count);
		}
	);

	invokeModule(serial_comm_module);


	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	return 0;
}
