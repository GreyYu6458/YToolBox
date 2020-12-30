#ifndef _TYPE2STRING_H_
#define _TYPE2STRING_H_
#include<iostream>

// 终止函数
template<class Last>
std::string type2string() {
	return std::string(typeid(Last).name());
}

// 通过模板获取类型的字符串
template<class First, class Second, class... _Args>
std::string type2string() {
	// low efficiency
	return std::string(typeid(First).name()) + " ||||| " + type2string<Second, _Args...>();
}

#endif