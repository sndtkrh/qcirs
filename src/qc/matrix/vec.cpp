#include "qc/matrix/matrix.hpp"

namespace qc {
std::string to_string( const std::complex<double> & z ){
  return std::to_string( std::real(z) ) + "+i" + std::to_string( std::imag(z) );
}
std::string to_string( const Vec & v ){
  std::string s = "";
  for(std::size_t i = 0; i < v.size(); i++){
    s += to_string( v[i] );
    if( i + 1 < v.size() )
      s += " ";
  }
  return s;
}
}
