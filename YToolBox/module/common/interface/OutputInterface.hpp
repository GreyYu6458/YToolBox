#ifndef _OUTPUT_INTERFACE_HPP_
#define _OUTPUT_INTERFACE_HPP_
#include "Interface.h"
#include "InputInterface.hpp"
#include "ILinkableInterface.h"
#include "common/module/BasicModule.h"
#include "common/tools/type2string.hpp"
#include <iostream>
#include <vector>

template <class... Args>
class OutputInterface : public ILinkableInterface
{
public:
	OutputInterface() {}

	virtual bool link_to(Interface* interface){
		if (interface->getInterfaceDirection() == INPUT && this->getTypeHash() == interface->getTypeHash()) {
			next_vector.push_back(dynamic_cast<InputInterface<Args...>*>(interface));
			return true;
		}
		return false;
	}

	void push(Args... args) {
		for (InputInterface<Args...>* elem : next_vector) {
			// TODO �����һ��ָ�����ͣ�ʹ��shared_ptr���з�װ�����ٿ��� 
			// ��opnecv�е�mat���Զ��������ݹ���
			elem->on_push(std::forward<Args>(args)...);
		}
	}

	virtual int getInterfaceDirection() {
		return OUTPUT;
	}

	virtual std::string getInterfaceTypeName() {
		return type2string<Args...>();
	}

	virtual size_t getTypeHash() {
		return typeid(InterfaceType<Args...>).hash_code();
	}

private:
	std::vector< InputInterface<Args...>* > next_vector;
};
#endif