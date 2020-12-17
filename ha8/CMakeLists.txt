cmake_minimum_required(VERSION 3.5)

project(ha8 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ha8
	mainwindow.h
	mainwindow.cpp
	mask.h
	mask.cpp
	features.h
	features.cpp
	model.h
	model.cpp
	calculate.cpp
	main.cpp
)

target_link_libraries(ha8 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS})

