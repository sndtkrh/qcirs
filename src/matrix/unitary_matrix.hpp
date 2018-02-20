#ifndef U_MATRIX
#define U_MATRIX
#include "square_matrix.hpp"
class UnitaryMat : public SquareMat {
public:
  UnitaryMat(){}
  UnitaryMat(std::vector<std::vector<std::complex<double>>> m){
    h = m.size();
    w = m[0].size();
    assert( h == w );
    N = h;
    for(int i = 0; i < N; i++){
      assert(m[i].size() == w);
    }
    A = m;
    Mat adjA = adj();
    assert( (operator*(adjA)).is_I() );
  }
};
#endif
