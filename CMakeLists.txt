cmake_minimum_required(VERSION 3.10)

project(ComputerVisionSystems)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_subdirectory(ha1)
add_subdirectory(ha2)
add_subdirectory(ha5)
add_subdirectory(ha7)
add_Subdirectory(ha8)
