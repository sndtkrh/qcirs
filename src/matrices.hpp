#ifndef MATRICES
#define MATRICES
#include "matrix/matrix.hpp"
#include "bitoperation.hpp"
const UnitaryMat I_2({
  {1,0},
  {0,1} });
const UnitaryMat PauliX({
  {0,1},
  {1,0} });
const UnitaryMat PauliY({
  {0, std::complex<double>(0,-1)},
  {std::complex<double>(0,1), 0} });
const UnitaryMat PauliZ({
  {1,0},
  {0,-1} });
const double sqrt2 = std::sqrt(2.0);
const UnitaryMat H( {
  {1/sqrt2, 1/sqrt2 },
  {1/sqrt2, -1/sqrt2}, });
const UnitaryMat CNOT( {
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 0, 1},
  {0, 0, 1, 0} });

const Vec v_zero = {1, 0};
const Vec v_one = {0, 1};
const Vec v_plus = {1/sqrt2, 1/sqrt2};
const Vec v_minus = {1/sqrt2, -1/sqrt2};

// f : {0,1}^n -> {0,1} |-> Uf : unitary transformation
UnitaryMat get_U(std::function<bool(std::size_t)> f, unsigned char n){
  std::size_t u_size = (1 << (n + 1));
  std::vector<Vec> A(u_size, Vec(u_size,0));
  for(std::size_t i = 0; i < (1 << n); i++){
    if( f(i) ){
      A[i * 2][i * 2]     = 0; A[i * 2][i * 2 + 1]     = 1;
      A[i * 2 + 1][i * 2] = 1; A[i * 2 + 1][i * 2 + 1] = 0;
    }else{
      A[i * 2][i * 2]     = 1; A[i * 2][i * 2 + 1]     = 0;
      A[i * 2 + 1][i * 2] = 0; A[i * 2 + 1][i * 2 + 1] = 1;
    }
  }
  return UnitaryMat(A);
}
#endif
