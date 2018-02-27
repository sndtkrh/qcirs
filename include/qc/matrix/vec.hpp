#ifndef VEC
#define VEC
#include <string>
#include <vector>
#include <complex>
typedef std::vector<std::complex<double>> Vec;

std::string to_string( const std::complex<double> & z );
std::string to_string( const Vec & v );
#endif
