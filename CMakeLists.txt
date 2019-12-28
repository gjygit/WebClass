cmake_minimum_required(VERSION 3.15)
project(WebClass)

set(CMAKE_CXX_STANDARD 14)

link_libraries(ws2_32)

add_executable(WebClass main.cpp)
add_executable(Server server.c)
add_executable(Clion client.c)