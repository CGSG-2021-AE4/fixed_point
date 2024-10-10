cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_TOOLCHAIN_FILE "X:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE string "")
project(fixed_point)


add_executable(${PROJECT_NAME} src/main.cpp "src/fixed_point_lib/fixed_point.h" "src/fixed_point_lib/meta.h")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

# Libs

find_package(benchmark CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE benchmark::benchmark benchmark::benchmark_main)