#include "MavlinkParseModule.h"
#include <boost/dll/alias.hpp>
#include <boost/dll/import.hpp>

MavlinkParseModule::MavlinkParseModule(){
	mav_status = new mavlink_status_t();
	mav_msg = new mavlink_message_t();
	std::unique_ptr<mavlink_status_t> a = std::make_unique<mavlink_status_t>();
	addtoInterfaceList("raw_bytes_ii", &raw_bytes_ii);
}

MavlinkParseModule::~MavlinkParseModule() {
	delete mav_status;
	delete mav_msg;
}

bool MavlinkParseModule::activate() {
	raw_bytes_ii.set_callback(&MavlinkParseModule::parse, this);
	return true;
}

bool MavlinkParseModule::deactivate() {
	return true;
}

std::string MavlinkParseModule::getModuleName() {
	return "MavlinkParseModule";
}

void MavlinkParseModule::set_parameters(const std::vector<std::pair<int, boost::any>>& params) {
	for (const auto& elem : params) {
		switch (elem.first) {
		case 0:
			chan = boost::any_cast<int>(elem.second);
		}
	}
}

std::vector<std::string> MavlinkParseModule::get_params_types(){
	return this->_type_name;
}

void inline MavlinkParseModule::parse(const char* bytes, size_t len) {
	for (size_t i = 0; i < len; i++) {
		bool parse_cmpt = mavlink_parse_char(this->chan, bytes[i], this->mav_msg, this->mav_status);
		if (parse_cmpt)
			printf("Received message with ID %d, sequence: %d from component %d of system %d \n",
				mav_msg->msgid, mav_msg->seq, mav_msg->compid, mav_msg->sysid);
	}
}

DEFINE_DYN_MODULE(MavlinkParseModule)
