#ifndef _INPUT_INTERFACE_HPP_
#define _INPUT_INTERFACE_HPP_
#include "Interface.h"
#include "common/module/BasicModule.h"
#include "common/tools/type2string.hpp"
#include <functional>


template <class... Args>
class InputInterface : public Interface {
public:

	// friend class OutputInterface<Args>;

	InputInterface(){}

	virtual ~InputInterface() {}

	InputInterface& operator=(const InputInterface&) = delete;

	void set_callback(const std::function<void(Args...)>& func){
		this->func = func;
	}

	template<class Type>
	void set_callback(void (Type::* method)(Args...), Type* instance) {
		this->func = m_bind(method, instance);
	}

	virtual int getInterfaceDirection() {
		return INPUT;
	}

	virtual std::string getInterfaceTypeName() {
		return type2string<Args...>();
	}

	virtual size_t getTypeHash() {
		return typeid(InterfaceType<Args...>).hash_code();
	}

	/// <summary>
	/// �����ӵ�OutputInterface����push����ʱ 
	/// ���Զ����ø÷���
	/// �÷�������һ��ִ��ĳһ�����ܻ����㷨
	/// ��������õ�����Ϣ(����Ž�����)
	/// </summary>
	/// <param name="...args"></param>
	inline void on_push(Args... args) {
		func(std::forward<Args>(args)...);
	}
private:
	/// <summary>
	///  ����һ�ּ򵥵�������������Ա�����󶨷���
	///  ͨ��lambdaʵ�֣���������ø÷�ʽ����Ҫʹ��ģ��ʵ��һ������������ռλ��������
	/// </summary>
	/// <typeparam name="R"> ��������ģ�����(�Զ��Ƶ�) </typeparam>
	/// <typeparam name="Type"> �󶨺����������� </typeparam>
	/// <param name="method"> ��Ա���� </param>
	/// <param name="instance"> �󶨺�������������� </param>
	/// <returns> �Ƶ��õ���std::function���� </returns>
	template<class R, class Type>
	std::function<R(Args...)> m_bind(R(Type::* method)(Args...), Type* instance)
	{
		return [=](Args&&... args) -> R
		{
			return (instance->*method)(std::forward<Args>(args)...);
		};
	}

	std::function<void(Args...)> func = [](Args...) {};
};

#endif
