cmake_minimum_required(VERSION 3.17)
project(opge)

set(CMAKE_CXX_STANDARD 17)

add_executable(pget main.cpp olcPixelGameEngine.h)

target_link_libraries(pget PRIVATE -lX11 -lGL -lpthread -lpng -lstdc++fs)
