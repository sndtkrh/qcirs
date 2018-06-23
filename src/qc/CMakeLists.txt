cmake_minimum_required(VERSION 2.8)

add_library(qc STATIC
  bitoperation.cpp matrices.cpp matrix_generator.cpp qalgorithm.cpp qcircuit.cpp
  qgate/qgate_custom.cpp qgate/qgate_qmux.cpp qgate/qgate_u.cpp qgate/qgate.cpp
  matrix/general_matrix.cpp matrix/square_matrix.cpp matrix/unitary_matrix.cpp matrix/vec.cpp)

install(TARGETS qc ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)
