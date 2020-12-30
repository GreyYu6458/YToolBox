#ifndef _BASCICMODULE_HPP_
#define _BASCICMODULE_HPP_
#include <iostream>
#include <vector>
#include "common/interface/Interface.h"
#include "common/module/Settable.h"
#include "common/module/WithInterface.h"

#include <unordered_map>
#include <boost/any.hpp>

/// <summary>
/// 一个模块可能是一个算法或者功能的模块
/// 或者是多个功能的整合
/// 一个模块可以对输入进行响应，
/// 并将结果进行输出
/// </summary>
class BasicModule :public WithInterface, public Settable{
public:
	virtual ~BasicModule() {}

	/// <summary>
	/// 激活模块，并对输入进行响应
	/// 并开始将响应结果输出
	/// </summary>
	virtual bool activate() = 0;

	/// <summary>
	/// 失效模块，它可能人会对输入进行响应(实现时应该避免)
	/// 但绝对不会产生输出
	/// </summary>
	virtual bool deactivate() = 0;

	/// <summary>
	/// 获得模块的名称
	/// </summary>
	virtual std::string get_moduleName() = 0;
};

/*
#define DEFINE_DYN_MODULE(MODULE_NAME, ...)										\
			static std::shared_ptr<MODULE_NAME>  create() {						\
				return std::move(std::make_shared<MODULE_NAME>(__VA_ARGS__));	\
			}BOOST_DLL_ALIAS(													\
				create,															\
				create_plugin													\
			)

*/
// std::shared_ptr<BasicModule> get_module(const boost::dll::shared_library& lib);

#endif