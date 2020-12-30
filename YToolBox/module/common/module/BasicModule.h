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
/// һ��ģ�������һ���㷨���߹��ܵ�ģ��
/// �����Ƕ�����ܵ�����
/// һ��ģ����Զ����������Ӧ��
/// ��������������
/// </summary>
class BasicModule :public WithInterface, public Settable{
public:
	virtual ~BasicModule() {}

	/// <summary>
	/// ����ģ�飬�������������Ӧ
	/// ����ʼ����Ӧ������
	/// </summary>
	virtual bool activate() = 0;

	/// <summary>
	/// ʧЧģ�飬�������˻�����������Ӧ(ʵ��ʱӦ�ñ���)
	/// �����Բ���������
	/// </summary>
	virtual bool deactivate() = 0;

	/// <summary>
	/// ���ģ�������
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