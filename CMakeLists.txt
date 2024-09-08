cmake_minimum_required(VERSION 3.29)
project(deadlock_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(src)

# Set Qt6_DIR to the directory containing Qt6Config.cmake
set(Qt6_DIR "/usr/lib/x86_64-linux-gnu/cmake/Qt6/")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

find_package(OpenGL REQUIRED)

add_executable(deadlock_simulator
        qt/Window.h
        qt/Window.cpp
        src/main.cpp
        src/Process.cpp
        src/Process.h
        src/Resource.cpp
        src/Resource.h
        src/DeadlockDetector.cpp
        src/DeadlockDetector.h
        src/BankersAlgorithm.cpp
        src/BankersAlgorithm.h
        tests/BankersAlgorithmTest.cpp
        tests/BankersAlgorithmTest.h
        tests/DeadlockTest.cpp
        tests/DeadlockTest.h
        tests/DeadlockAvoidanceTest.cpp
        tests/DeadlockAvoidanceTest.h
        tests/DeadlockRecoveryTest.cpp
        tests/DeadlockRecoveryTest.h
        src/DeadlockRecovery.cpp
        src/DeadlockRecovery.h
        src/DeadlockAvoidance.cpp
        src/DeadlockAvoidance.h
        src/Deadlock.cpp
        src/Deadlock.h
        src/Simulation.cpp
        src/Simulation.h
        src/Event.cpp
        src/Event.h
        src/EventQueue.cpp
        src/EventQueue.h
)

target_link_libraries(deadlock_simulator
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        ${OPENGL_LIBRARIES}
)
