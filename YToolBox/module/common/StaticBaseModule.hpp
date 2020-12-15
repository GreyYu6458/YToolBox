#ifndef _BASEMODULE_H_
#define _BASEMODULE_H_
#include <iostream>
#include <functional>
#include <type_traits>

/*
 * 这是用奇异模板递归技术实现的模块类型,它支持任意类型的输入和输出(通过定义回调)
 * 这种方式比多态指针快的多
 * 
 * 这个模块对参数输入很敏感，他的设计目的是在编译期可以接受任意的参数类型，并提供对应
 * 的事件响应（事件响应的回调参数类型由子类定义的回调函数参数指定）
*/


/*
* 该宏的作用为将基类申明为子类的友元，由于宏:YModuleDefineEventCb注册的是私有方法
* 若没有标明该宏，将会由于权限问题，编译出错
*/
#define YModule(moduleName) friend StaticBaseModule<moduleName>;

/*
* 该宏仅是对申明回调方法的一些封装:一个_FUNCTION_NS funtion，若干方法
* 使用需要在类中注明宏:YModule(类名)
* 
* 宏的第一个参数是注册的事件名称，实际上是调用的函数名称
* 宏的第2+n个参数是回调函数的类型
* 
* 注意!:由于带有模板，这个类将不可使用文件上的类和实现分离，
* 解决方法一:
*	使用#include<xxx.cpp>
* 
* 解决方法二:
* 可以手动展开宏定义中的模板
* 具体的形式为:
*	先定义一个函数
*	std::function<void(参数类型)> EVENT = [](参数类型){} // 空lambda防止崩溃
* 
* 	void setEventCbImpl(const std::function<void(参数类型)>& func) {
*		EVENT = func;
*	}
*	或者
*	void setEventCbImpl(T& obj, void (T::*func)(参数类型)) { // 其中T为目标类的类型
*		EVENT = std::bind(func, &obj, std::placeholders::_1);
*	}
* 这种方式将不使用模板，将可以使用类和实现的分离
*/
#define YModuleDefineEventCb(EVENT, ...)\
private:\
	std::function<void(__VA_ARGS__)> EVENT = [](__VA_ARGS__){}; \
public:\
	template<class _F> void set_ ##EVENT ##_call_back(_F& obj, void (_F::*func)(__VA_ARGS__)) {\
		EVENT = std::bind(func, &obj, std::placeholders::_1);\
	}\
	void set_ ##EVENT ##_call_back(const std::function<void(__VA_ARGS__)>& func) {\
		EVENT = func;\
	}

/*
* 调用宏:YModuleDefineEventCb中申明的事件
*/
#define YModuleInvokeEventCb(EVENT , ...) EVENT(__VA_ARGS__)
	

template<class Derived> class StaticBaseModule; 


template<class _BMT, class... ARGS>
void invokeModule(StaticBaseModule<_BMT>& module, ARGS&&... args) {
	module.start(std::forward<ARGS>(args)...);
}

template<class Derived>
class StaticBaseModule {
public:
	template<class _BMT, class... ARGS>	friend void invokeModule(StaticBaseModule<_BMT>& module, ARGS&&... args);

	~StaticBaseModule(){}
private:
	template<class... ARGS> 
	void start(ARGS&&... args) {
		static_cast<Derived*>(this)->execute(std::forward<ARGS>(args)...);
	}

	template<class... ARGS> inline void  execute(ARGS&&... args) {}

	inline void  execute() {}
};



#endif