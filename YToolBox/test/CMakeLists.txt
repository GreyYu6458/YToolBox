# CMakeList.txt: YToolBox 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
project(ModuleTest)

cmake_minimum_required (VERSION 3.8)

set(test_dir ${ModuleTest_SOURCE_DIR})
message("SOURCE_DIR:${test_dir}")

include_directories(${test_dir}/../module/common)

###################################################
link_directories(
	${Boost_LIBRAYIES_DIR}
)

add_library(basic_module
STATIC

"${test_dir}/../module/common/module/WithInterface.cpp"
"${test_dir}/../module/common/module/Settable.cpp"
"${test_dir}/../module/common/exception/LinkException.cpp"
)

###################################################
add_library(mavlink_parse_module
SHARED
"${test_dir}/../module/decode/mavlink/MavlinkParseModule.cpp"
)

target_link_libraries(mavlink_parse_module
basic_module
)
###################################################
add_library(serial_comm_module
SHARED
"${test_dir}/../module/io/serial/SerialCommModule.cpp"
)

target_link_libraries(serial_comm_module
basic_module
)
###################################################
# 将源代码添加到此项目的可执行文件。


add_executable (moduleTest 
"ModuleTest.cpp" 
)

target_link_libraries(moduleTest
basic_module
)

message("Boost include ${Boost_INCLUDE_DIRS}")
message("Boost library ${Boost_LIBRAYIES_DIR}")
