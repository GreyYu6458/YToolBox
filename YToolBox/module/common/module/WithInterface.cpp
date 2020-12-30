#include "WithInterface.h"


const Interface* WithInterface::get_interface(const std::string& name)
{
	if (interface_map.count(name) != 0) {
		return interface_map[name];
	}
	return nullptr;
}

std::vector<std::pair<std::string, Interface*>> WithInterface::get_interfaces() {
	std::vector<std::pair<std::string, Interface*>> _v;
	for (auto& elem : interface_map) {
		_v.push_back(elem);
	}
	return _v;
}

bool WithInterface::add_interface(const std::string& name, Interface* itfc)
{
	if (interface_map.count(name) == 0) 
	{
		interface_map[name] = itfc;
		return true;
	}
	return false;
}