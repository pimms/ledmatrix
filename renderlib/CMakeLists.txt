cmake_minimum_required(VERSION 3.7)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(renderlib LANGUAGES CXX)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message("📺 Using HZeller RPI RGB LED Matrix library")
    file(GLOB_RECURSE SRC 
        rpi-rgb-led-matrix/include/* 
        rpi-rgb-led-matrix/lib/*
        hzeller/**.h 
        hzeller/**.cpp
    )
else()
    message("📺 Using dummy rendering library")
    file(GLOB_RECURSE SRC 
        dummy/**.h 
        dummy/**.cpp
    )
endif()

add_library(renderlib ${SRC})
set(RENDERLIB_INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(rpi-rgb-led-matrix/include/)
