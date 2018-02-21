cmake_minimum_required(VERSION 2.8)
project(qcirs)

include_directories("${PROJECT_SOURCE_DIR}/include")
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra")
add_subdirectory(src)
