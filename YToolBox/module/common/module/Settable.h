#ifndef _SETTABLE_H_
#define _SETTABLE_H_
#include <iostream>
#include <vector>
#include <functional>
#include <common/parameter/Parameters.h>
#include <boost/any.hpp>

// bool byte int32 uint32 int64 uint64 float32 float64
// picture string 

// ��settable��ע���������
// ��ʵ������ʱ��ִ�ж�Ӧ���������ò���
class Settable {
	typedef std::tuple<bool, bool, std::string, std::function<int(boost::any)>> param_info;
	int set(int index, boost::any _val);

	bool is_all_nessary_param_set();
protected:
	// ģ�����б�Ҫ�Ĳ����� ��ģ�鼤��ʱ������Щ�������м��
	void register_nessary_param(
		bool is_nessary,
		const std::string& desription, 
		const std::function<int (boost::any)>& func
		);

	int register_nessary_param(
		bool is_nessary,
		const std::string& desription,
		const std::function<int (boost::any)>& func,
		boost::any default_value
		);

private:
	std::vector<param_info> _param_list;
};


#endif