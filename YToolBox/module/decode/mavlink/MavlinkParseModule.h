#ifndef _MAVLINK_MODULE_H_
#define _MAVLINK_MODULE_H_
#include "common/module/BasicModule.h"
#include "common/interface/InputInterface.hpp"
#include "common/interface/OutputInterface.hpp"
#ifdef __cplusplus
extern "C" {
#include "c_library_v2/common/mavlink.h"
}
#endif
#include <iostream>
#include <functional>

class MavlinkParseModule : public BasicModule {
private:
	InputInterface<const char*, size_t> raw_bytes_ii;
public:

	MavlinkParseModule();

	~MavlinkParseModule();

	virtual bool activate();

	virtual bool deactivate();

	virtual std::string getModuleName();

	// ����ģ��Ĳ���
	// ��ϸ�Ĳ���
	// ���:0 ����:int ����:����mavlinkͨ��
	virtual void set_parameters(const std::vector<std::pair<int, boost::any>>& params);

	virtual std::vector<std::string> get_params_types();
private:
	std::vector<std::string> _type_name{"int"};

	void parse(const char* bytes, size_t len);

	mavlink_status_t* mav_status;
	mavlink_message_t* mav_msg;
	char chan{0};
};

#endif