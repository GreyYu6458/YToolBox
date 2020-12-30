#ifndef _TYPE2STRING_H_
#define _TYPE2STRING_H_
#include<iostream>

// ��ֹ����
template<class Last>
std::string type2string() {
	return std::string(typeid(Last).name());
}

// ͨ��ģ���ȡ���͵��ַ���
template<class First, class Second, class... _Args>
std::string type2string() {
	// low efficiency
	return std::string(typeid(First).name()) + " ||||| " + type2string<Second, _Args...>();
}

#endif