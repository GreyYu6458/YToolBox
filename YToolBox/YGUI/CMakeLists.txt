cmake_minimum_required(VERSION 3.8)
project(YGUI LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Qt5_DIR "D:/DevelopmentKits/c_cpp/Qt/5.15.1/msvc2019_64/lib/cmake/Qt5")
set(CMAKE_PREFIX_PATH "D:/DevelopmentKits/c_cpp/Qt/5.15.1/msvc2019_64")
set(QT_DIR "D:/DevelopmentKits/c_cpp/Qt/5.15.1/msvc2019_64/lib/cmake/Qt5")
set(QT_QMAKE_EXECUTABLE "D:/DevelopmentKits/c_cpp/Qt/5.15.1/msvc2019_64/bin/qmake.exe")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

include_directories(
	inc
)

add_executable(YGUI
	
  src/main.cpp
  src/mainwindow.cpp
  inc/mainwindow.h		# 不能忽略添加头文件，因为需要QT moc将其编译成标准C语言
  src/mainwindow.ui
)
target_link_libraries(YGUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

