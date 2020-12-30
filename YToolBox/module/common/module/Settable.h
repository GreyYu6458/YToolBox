#ifndef _SETTABLE_H_
#define _SETTABLE_H_
#include <iostream>
#include <vector>
#include <functional>
#include <common/parameter/Parameters.h>
#include <boost/any.hpp>

// bool byte int32 uint32 int64 uint64 float32 float64
// picture string 

// 在settable中注册参数类型
// 在实际运行时，执行对应函数，设置参数
class Settable {
	typedef std::tuple<bool, bool, std::string, std::function<int(boost::any)>> param_info;
	int set(int index, boost::any _val);

	bool is_all_nessary_param_set();
protected:
	// 模块运行必要的参数， 在模块激活时，对这些参数进行检测
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