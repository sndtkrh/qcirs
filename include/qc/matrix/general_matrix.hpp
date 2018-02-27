#ifndef G_MATRIX
#define G_MATRIX
#include "vec.hpp"
class Mat {
public:
  Mat();
  Mat(std::vector<std::vector<std::complex<double>>> B);
  const Vec & row_at(std::size_t i) const;
  const std::complex<double> & at(std::size_t i, std::size_t j) const;
  std::size_t rows() const;
  std::size_t cols() const;
  Mat operator * (const Mat & B) const;
  Vec operator * (const Vec & v) const;
  Mat adj() const;
  bool is_I() const;
protected:
  const double eps = 1e-9;
  std::size_t h, w;
  std::vector<Vec> A;
};

std::string to_string(const Mat & A);
#endif
