#ifndef _WITH_INTERFACE_H_
#define _WITH_INTERFACE_H_
#include <iostream>
#include <unordered_map>
#include <common/interface/Interface.h>

class WithInterface {
public:
	const Interface* get_interface(const std::string& name);

	std::vector<std::pair<std::string, Interface*>> get_interfaces();

protected:
	bool add_interface(const std::string& name, Interface* itfc);

private:
	std::unordered_map<std::string, Interface*> interface_map;
};

#endif