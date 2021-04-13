cmake_minimum_required(VERSION 3.17)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(chillness_1.1.3 main.cpp)

target_link_libraries(chillness_1.1.3 sfml-graphics sfml-audio sfml-network)