cmake_minimum_required(VERSION 4.0)
project(sufa)

set(CMAKE_CXX_STANDARD 17)

add_executable(sufa main.cpp
        home.cpp
        home.h
        cmd/command.h
        cmd/cd_command.cpp
        cmd/cd_command.h
)
