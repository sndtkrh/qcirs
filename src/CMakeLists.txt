cmake_minimum_required(VERSION 2.8)
project(qcirs)

add_subdirectory(qc)
add_subdirectory(qcparser)

add_executable(qcirs main.cpp)
target_link_libraries(qcirs qcparser)
