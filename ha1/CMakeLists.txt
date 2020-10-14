add_executable(ha1 src/ha1.cpp)
target_link_libraries( ha1 ${OpenCV_LIBS} )
target_compile_options(ha1 PRIVATE -Wall -Werror)
