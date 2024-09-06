cmake_minimum_required(VERSION 3.29)
project(deadlock_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(src)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

find_package(OpenGL REQUIRED)

add_executable(deadlock_simulator
        src/Resource.cpp
        src/Resource.h
        src/Process.cpp
        src/Process.h
        src/Simulation.cpp
        src/Simulation.h
        tests/testBasicFunctionality.cpp
        tests/testBasicFunctionality.h
        qt/main.cpp
        qt/Window.h
        qt/Window.cpp
        utils/detectionUtils.cpp
        utils/detectionUtils.h
)

target_link_libraries(deadlock_simulator
        Qt::Core
        Qt::Gui
        Qt::Widgets
        ${OPENGL_LIBRARIES}
)
