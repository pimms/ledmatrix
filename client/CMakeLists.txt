cmake_minimum_required(VERSION 3.10)

project(ledclient LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)

file(GLOB_RECURSE SRC src/**.cpp)
file(GLOB_RECURSE HDR src/**.h)

add_executable(ledclient ${SRC} ${HDR})

if (WIN32)
    set(WINLIBS Ws2_32.lib)
    # target_link_libraries(ledclient Ws2_32.lib)
endif()

find_package(cimg CONFIG REQUIRED)
target_link_libraries(ledclient PRIVATE ${WINLIBS} CImg::CImg)

