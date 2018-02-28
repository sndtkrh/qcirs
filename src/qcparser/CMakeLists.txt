cmake_minimum_required(VERSION 2.8)
project(qcparser)

add_library(qcparser STATIC
  parser.cpp interpreter.cpp)
target_link_libraries(qcparser qcirs)
