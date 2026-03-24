cmake_minimum_required(VERSION 3.7)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ledmatrix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

file(GLOB_RECURSE SRC src/**.cpp)
file(GLOB_RECURSE HDR src/**.h)

add_subdirectory(renderlib)

add_executable(ledmatrix ${HZLIB} ${SRC} ${HDR})
include_directories(renderlib/include)
target_link_libraries(ledmatrix renderlib)

