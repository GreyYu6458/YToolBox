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
	/// 当连接的OutputInterface调用push方法时 
	/// 会自动调用该方法
	/// 该方法并不一定执行某一个功能或者算法
	/// 仅仅处理得到的消息(例如放进队列)
	/// </summary>
	/// <param name="...args"></param>
	inline void on_push(Args... args) {
		func(std::forward<Args>(args)...);
	}
private:
	/// <summary>
	///  这是一种简单的任意参数，类成员函数绑定方法
	///  通过lambda实现，如果不采用该方式，需要使用模板实现一个任意数量的占位符生成器
	/// </summary>
	/// <typeparam name="R"> 返回类型模板参数(自动推导) </typeparam>
	/// <typeparam name="Type"> 绑定函数持有者类 </typeparam>
	/// <param name="method"> 成员函数 </param>
	/// <param name="instance"> 绑定函数持有者类对象 </param>
	/// <returns> 推导得到的std::function对象 </returns>
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
