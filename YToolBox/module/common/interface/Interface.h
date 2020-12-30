#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include <iostream>
#include <type_traits>

template<class... Args>
struct InterfaceType {};

struct Interface {
	enum {
		OUTPUT = 0,
		INPUT
	};

	virtual ~Interface() {}

	virtual int getInterfaceDirection() = 0;

	virtual std::string getInterfaceTypeName() = 0;

	virtual size_t getTypeHash() = 0;
};

#endif