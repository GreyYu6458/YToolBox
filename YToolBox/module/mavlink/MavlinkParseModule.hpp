#ifndef _MAVLINK_MODULE_H_
#define _MAVLINK_MODULE_H_
#include "common/StaticBaseModule.hpp"
#ifdef __cplusplus
extern "C" {
#include "c_library_v2/common/mavlink.h"
}
#endif
#include <iostream>
#include <functional>

#define MAVLINKEventDefine(EVENT) YModuleDefineEventCb(EVENT, const mavlink_message_t&, const mavlink_status_t&)

class MavlinkParseModule : public StaticBaseModule<MavlinkParseModule> {
public:
	YModule(MavlinkParseModule)

	MavlinkParseModule(char _chan = 0) :chan(_chan) {
		mav_status = new mavlink_status_t();
		mav_msg = new mavlink_message_t();
	}

	~MavlinkParseModule() {
		delete mav_status;
		delete mav_msg;
	}

	MAVLINKEventDefine(on_parsed)
private:
	void inline execute(const char* bytes, size_t len) {
		for (size_t i = 0; i < len; i++) {
			bool parse_cmpt = mavlink_parse_char(this->chan, bytes[i], this->mav_msg, this->mav_status);
			if (parse_cmpt)
				YModuleInvokeEventCb(on_parsed, *mav_msg, *mav_status);
		}
	}

	void inline execute(const std::string& bytes) {
		this->execute(bytes.c_str(), bytes.size());
	}

	mavlink_status_t* mav_status;
	mavlink_message_t* mav_msg;
	char chan;
};


#endif