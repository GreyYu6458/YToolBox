include_directories(module)


set(Boost_LIBRAYIES_DIR "D:/DevelopmentKits/c_cpp/Boost/boost_1_74_0/lib" )
set(Boost_INCLUDE_DIRS "D:/DevelopmentKits/c_cpp/Boost/boost_1_74_0/include/boost-1_74")
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(test)
