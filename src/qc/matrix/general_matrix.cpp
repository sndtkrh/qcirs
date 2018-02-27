#include "qc/matrix/general_matrix.hpp"
#include <cassert>

Mat::Mat(){}
Mat::Mat(std::vector<std::vector<std::complex<double>>> B){
  h = B.size();
  w = B[0].size();
  std::size_t hB = B.size();
  std::size_t wB = B[0].size();
  for( auto & row : A ){
    assert( row.size() == w );
  }
  assert( hB == h );
  assert( wB == w );
  A = B;
}
const Vec & Mat::row_at(std::size_t i) const {
  return A[i];
}
const std::complex<double> & Mat::at(std::size_t i, std::size_t j) const {
  return A[i][j];
}
std::size_t Mat::rows() const {
  return h;
}
std::size_t Mat::cols() const {
  return w;
}
Mat Mat::operator * (const Mat & B) const {
  std::vector<Vec> ab( h, Vec(B.cols(), 0));
  assert( w == B.rows() );
  for(std::size_t i = 0; i < h; i++){
    for(std::size_t j = 0; j < B.cols(); j++){
      for(std::size_t k = 0; k < w; k++){
        ab[i][j] += A[i][k] * B.at(k, j);
      }
    }
  }
  Mat AB( ab );
  return AB;
}
Vec Mat::operator * (const Vec & v) const {
  Vec u(h, 0);
  assert( w == v.size() );
  for(std::size_t i = 0; i < h; i++){
    for(std::size_t j = 0; j < w; j++){
      u[i] += A[i][j] * v[j];
    }
  }
  return u;
}
Mat Mat::adj() const {
  std::vector<Vec> adjA(w, Vec(h));
  for(std::size_t i = 0; i < h; i++){
    for(std::size_t j = 0; j < w; j++){
      adjA[j][i] = std::conj( A[i][j] );
    }
  }
  return Mat(adjA);
}
bool Mat::is_I() const {
  if( h == w ){
    for(std::size_t i = 0; i < h; i++){
      for(std::size_t j = 0; j < w; j++){
        if( abs( A[i][j] - ( (i==j) ? 1.0 : 0 ) ) > eps ){
          return false;
        }
      }
    }
    return true;
  }
  return false;
}

std::string to_string(const Mat & A) {
  std::string s = "";
  for(std::size_t i = 0; i < A.cols(); i++){
    s += to_string( A.row_at(i) );
    s += (i == A.cols() - 1) ? "" : "\n";
  }
  return s;
}
