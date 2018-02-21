#ifndef SQ_MAT
#define SQ_MAT
#include "general_matrix.hpp"
class SquareMat : public Mat {
public:
  SquareMat(){}
  SquareMat(std::vector<std::vector<std::complex<double>>> m){
    h = m.size();
    w = m[0].size();
    assert( h == w );
    N = h;
    for(std::size_t i = 0; i < N; i++){
      assert(m[i].size() == w);
    }
    A = m;
  }
  std::size_t size() const {
    return N;
  }
protected:
  std::size_t N;
};
#endif
