#include "Settable.h"

int Settable::set(int index, boost::any _val)
{
	int set_result = std::get<3>(_param_list[index])(_val);
	if(!set_result)
	{
		std::get<1>(_param_list[index]) = true;
		return 0;
	}
	return set_result;
}

void Settable::register_nessary_param(	bool is_nessary, const std::string& desription, 
										const std::function<int(boost::any)>& func)
{
	_param_list.push_back(param_info(is_nessary, false, desription, func));
}

int Settable::register_nessary_param(	bool is_nessary, const std::string& desription, 
										const std::function<int(boost::any)>& func, boost::any default_value)
{
	int set_result = func(default_value);
	if (!set_result)
	{
		_param_list.push_back(param_info(is_nessary, true, desription, func));
		return 0;
	}
	return set_result;
}

bool Settable::is_all_nessary_param_set()
{
	for (auto i = 0; i < _param_list.size(); i++)
	{
		if (!std::get<0>(_param_list[i]))
			continue;
		else if (!std::get<1>(_param_list[i]))
			return false;
	}
	return true;
}