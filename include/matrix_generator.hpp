#ifndef MGEN
#define MGEN
#include "common.hpp"
class MatrixGenerator{
public:
  ~MatrixGenerator(){
    for(Mat * M : Ms){
      delete M;
    }
  }
  // unitary matrix for quantum Fourier transformation
  UnitaryMat * get_qft(qbitsize qbit_n){
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
    UnitaryMat * p = new UnitaryMat(A);
    Ms.push_back(p);
    return p;
  }
private:
  std::vector<Mat *> Ms;
};
#endif
