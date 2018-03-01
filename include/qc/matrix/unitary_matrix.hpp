#ifndef U_MATRIX
#define U_MATRIX
namespace qc {
  class UnitaryMat : public SquareMat {
  public:
    UnitaryMat();
    UnitaryMat(std::vector<std::vector<std::complex<double>>> m);
  };
}
#endif
