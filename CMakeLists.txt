cmake_minimum_required(VERSION 3.9)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ledmatrix LANGUAGES CXX)
include_directories(src)

file(GLOB_RECURSE SRC src/**.cpp)
file(GLOB_RECURSE HDR src/**.h)

#find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)
#include_directories(${SFML_INCLUDE_DIR})
#link_directories(/opt/homebrew/lib/)
#target_link_libraries(stingray sfml-graphics sfml-window sfml-system)

add_executable(ledmatrix ${SRC} ${HDR})
set_property(TARGET ledmatrix PROPERTY CXX_STANDARD 20)
target_compile_features(ledmatrix PRIVATE cxx_std_20)
