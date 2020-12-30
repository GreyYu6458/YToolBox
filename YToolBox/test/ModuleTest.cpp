// YToolBox.cpp: 定义应用程序的入口点。
#include "common/module/BasicModule.h"

const char* path = "D:/Project/CodeRepo/c_cpp/YToolBox/out/build/x64-Release/YToolBox/test/mavlink_parse_module.dll";

int main()
{
	auto dll = boost::dll::shared_library(path, boost::dll::load_mode::append_decorations);
	try {
		auto module_sptr = get_module(dll);
		std::cout << module_sptr->getModuleName() << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}


	return 0;
}
