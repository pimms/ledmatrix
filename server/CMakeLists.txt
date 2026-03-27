cmake_minimum_required(VERSION 3.7)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ledserver LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message("📺 Using HZeller RPI RGB LED Matrix library")
    file(GLOB_RECURSE RENDERSRC 
        rpi-rgb-led-matrix/include/* 
        rpi-rgb-led-matrix/lib/**.cc
        rpi-rgb-led-matrix/lib/**.c
        hzeller/**.h 
        hzeller/**.cpp
    )
else()
    message("📺 Using dummy rendering library")
    file(GLOB_RECURSE RENDERSRC
        dummy/**.h 
        dummy/**.cpp
    )
endif()

file(GLOB_RECURSE SRC src/**.h src/**.cpp)

add_executable(ledserver ${RENDERSRC} ${SRC})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rpi-rgb-led-matrix/include/)
