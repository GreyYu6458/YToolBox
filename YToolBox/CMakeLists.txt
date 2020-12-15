include_directories(module)


set(CMAKE_PREFIX_PATH "D:/DevelopmentKits/c_cpp/Boost/boost_1_74_0")
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


add_subdirectory(YGUI)

add_subdirectory(module/test)
