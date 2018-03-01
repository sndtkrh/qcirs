#ifndef SQ_MAT
#define SQ_MAT
namespace qc {
  class SquareMat : public Mat {
  public:
    SquareMat();
    SquareMat(std::vector<std::vector<std::complex<double>>> m);
    std::size_t size() const;
  protected:
    std::size_t N;
  };
}
#endif
