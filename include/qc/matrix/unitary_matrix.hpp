#ifndef U_MATRIX
#define U_MATRIX
#include "square_matrix.hpp"
class UnitaryMat : public SquareMat {
public:
  UnitaryMat();
  UnitaryMat(std::vector<std::vector<std::complex<double>>> m);
};
#endif
