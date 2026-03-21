cmake_minimum_required(VERSION 3.7)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ledmatrix LANGUAGES CXX)
include_directories(src)

file(GLOB_RECURSE SRC src/**.cpp)
file(GLOB_RECURSE HDR src/**.h)

add_executable(ledmatrix ${SRC} ${HDR})
#set_property(TARGET ledmatrix PROPERTY CXX_STANDARD 11)
#target_compile_features(ledmatrix PRIVATE cxx_std_11)
