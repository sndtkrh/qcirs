cmake_minimum_required(VERSION 2.8)
project(main)

add_subdirectory(qc)
add_subdirectory(qcparser)

add_executable(main main.cpp)
target_link_libraries(main qcparser)
