#ifndef MGEN
#define MGEN
#include "common.hpp"
class MatrixGenerator{
public:
  ~MatrixGenerator();
  UnitaryMat * get_I(std::size_t s);
  // unitary matrix for quantum Fourier transformation
  UnitaryMat * get_qft(qbitsize qbit_n);
private:
  std::map<std::size_t, UnitaryMat *> memo_I;
  std::map<qbitsize, UnitaryMat *> memo_qft;
  std::vector<Mat *> Ms;
};
#endif
