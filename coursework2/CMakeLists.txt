cmake_minimum_required(VERSION 3.23)
project(coursework2)

set(CMAKE_CXX_STANDARD 14)

add_executable(coursework2 main.cpp Button.h Field.h Button.cpp Field.cpp Cfg.cpp Cfg.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR F:/Libs/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS audio system window graphics REQUIRED)

include_directories(F:/Libs/SFML-2.5.1/include/SFML)


target_link_libraries(coursework2 sfml-graphics)