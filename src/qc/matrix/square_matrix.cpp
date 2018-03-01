#include "qc/matrix/matrix.hpp"

namespace qc {
SquareMat::SquareMat(){}
SquareMat::SquareMat(std::vector<std::vector<std::complex<double>>> m){
  h = m.size();
  w = m[0].size();
  assert( h == w );
  N = h;
  for(std::size_t i = 0; i < N; i++){
    assert(m[i].size() == w);
  }
  A = m;
}
std::size_t SquareMat::size() const {
  return N;
}
}
