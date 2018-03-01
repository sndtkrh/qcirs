#include "qc/matrix/matrix.hpp"

namespace qc {
UnitaryMat::UnitaryMat(){}
UnitaryMat::UnitaryMat(std::vector<std::vector<std::complex<double>>> m){
  h = m.size();
  w = m[0].size();
  assert( h == w );
  N = h;
  for(std::size_t i = 0; i < N; i++){
    assert(m[i].size() == w);
  }
  A = m;
  Mat adjA = adj();
  assert( (operator*(adjA)).is_I() );
}
}
