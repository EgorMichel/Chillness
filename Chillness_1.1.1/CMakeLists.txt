cmake_minimum_required(VERSION 3.17)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(Chillness_1.1.1 main.cpp)

target_link_libraries(Chillness_1.1.1 sfml-graphics sfml-audio)