cmake_minimum_required(VERSION 2.8)

add_library(qcirs STATIC
  matrix/vec.cpp matrix/general_matrix.cpp matrix/square_matrix.cpp matrix/unitary_matrix.cpp
  bitoperation.cpp matrices.cpp matrix_generator.cpp qalgorithm.cpp
  qcircuit.cpp
  qgate/qgate.cpp qgate/qgate_qmux.cpp qgate/qgate_u.cpp qgate/qgate_custom)
