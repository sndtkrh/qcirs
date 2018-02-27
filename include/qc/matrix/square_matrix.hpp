#ifndef SQ_MAT
#define SQ_MAT
#include "general_matrix.hpp"
class SquareMat : public Mat {
public:
  SquareMat();
  SquareMat(std::vector<std::vector<std::complex<double>>> m);
  std::size_t size() const;
protected:
  std::size_t N;
};
#endif
