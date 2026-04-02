cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(ledmatrix)

add_subdirectory(client)
add_subdirectory(server)
