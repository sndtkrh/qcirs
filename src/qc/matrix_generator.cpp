#include "qc/common.hpp"
#include "qc/matrix_generator.hpp"

namespace qc {
MatrixGenerator::~MatrixGenerator(){
  for(Mat * M : Ms){
    delete M;
  }
}
UnitaryMat * MatrixGenerator::get_I(std::size_t s){
  if( memo_I.find(s) != memo_I.end() ){
    return memo_I[s];
  }
  std::vector<Vec> A(s, Vec(s, 0));
  for(std::size_t i = 0; i < s; i++){
    A[i][i] = 1;
  }
  memo_I[s] = new UnitaryMat(A);
  Ms.push_back( memo_I[s] );
  return memo_I[s];
}
// unitary matrix for quantum Fourier transformation
UnitaryMat * MatrixGenerator::get_qft(qbitsize qbit_n){
  if( memo_qft.find(qbit_n) != memo_qft.end() ){
    return memo_qft[qbit_n];
  }
  const double pi = std::acos(-1);
  std::size_t s = (1 << qbit_n);
  std::vector<Vec> A(s, Vec(s, 0));
  comp omega = std::polar(1.0, 2 * pi / s);
  std::vector<comp> powomega(s);
  powomega[0] = 1;
  for(std::size_t k = 1; k < s; k++){
    powomega[k] = powomega[k-1] * omega;
  }
  for(std::size_t i = 0; i < s; i++){
    for(std::size_t j = 0; j < s; j++){
      A[i][j] = 1.0 / sqrt(s) * powomega[(i * j) % s];
    }
  }
  memo_qft[qbit_n] = new UnitaryMat(A);
  Ms.push_back( memo_qft[qbit_n] );
  return memo_qft[qbit_n];
}
}
