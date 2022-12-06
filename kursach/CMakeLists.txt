cmake_minimum_required(VERSION 3.22)
project(kursach)

set(CMAKE_CXX_STANDARD 20)

add_executable(kursach main.cpp src/Svg.h src/Figures.cpp src/Figures.h src/Svg.cpp src/Algorithm.cpp src/Algorithm.h src/Gcode.cpp src/Gcode.h test/AlgorithmTests.h)


#set(SFML_STATIC_LIBRARIES TRUE)
#set(SFML_DIR F:/Libs/SFML-2.5.1/lib/cmake/SFML)
#find_package(SFML COMPONENTS system window graphics audio REQUIRED)

#include_directories(F:/Libs/SFML-2.5.1/include/SFML)


#target_link_libraries(kursach sfml-graphics)