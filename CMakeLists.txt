cmake_minimum_required(VERSION 3.29)
project(deadlock_simulator)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(deadlock_simulator
        src/Resource.cpp
        src/Resource.h
        src/Process.cpp
        src/Process.h
        src/Simulation.cpp
        src/Simulation.h
        tests/testBasicFunctionality.cpp
        tests/testBasicFunctionality.h
)
