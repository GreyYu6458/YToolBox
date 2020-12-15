#ifndef _BASEMODULE_H_
#define _BASEMODULE_H_
#include <iostream>
#include <functional>
#include <type_traits>

/*
 * ����������ģ��ݹ鼼��ʵ�ֵ�ģ������,��֧���������͵���������(ͨ������ص�)
 * ���ַ�ʽ�ȶ�ָ̬���Ķ�
 * 
 * ���ģ��Բ�����������У��������Ŀ�����ڱ����ڿ��Խ�������Ĳ������ͣ����ṩ��Ӧ
 * ���¼���Ӧ���¼���Ӧ�Ļص��������������ඨ��Ļص���������ָ����
*/


/*
* �ú������Ϊ����������Ϊ�������Ԫ�����ں�:YModuleDefineEventCbע�����˽�з���
* ��û�б����ú꣬��������Ȩ�����⣬�������
*/
#define YModule(moduleName) friend StaticBaseModule<moduleName>;

/*
* �ú���Ƕ������ص�������һЩ��װ:һ��_FUNCTION_NS funtion�����ɷ���
* ʹ����Ҫ������ע����:YModule(����)
* 
* ��ĵ�һ��������ע����¼����ƣ�ʵ�����ǵ��õĺ�������
* ��ĵ�2+n�������ǻص�����������
* 
* ע��!:���ڴ���ģ�壬����ཫ����ʹ���ļ��ϵ����ʵ�ַ��룬
* �������һ:
*	ʹ��#include<xxx.cpp>
* 
* ���������:
* �����ֶ�չ���궨���е�ģ��
* �������ʽΪ:
*	�ȶ���һ������
*	std::function<void(��������)> EVENT = [](��������){} // ��lambda��ֹ����
* 
* 	void setEventCbImpl(const std::function<void(��������)>& func) {
*		EVENT = func;
*	}
*	����
*	void setEventCbImpl(T& obj, void (T::*func)(��������)) { // ����TΪĿ���������
*		EVENT = std::bind(func, &obj, std::placeholders::_1);
*	}
* ���ַ�ʽ����ʹ��ģ�壬������ʹ�����ʵ�ֵķ���
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
* ���ú�:YModuleDefineEventCb���������¼�
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