#ifndef BITOP
#define BITOP
#include "common.hpp"
#include <vector>
typedef std::size_t S;

S bitat(S a, qbitsize idx){
  return 1 & (a >> idx);
}

void bitsetat(S & a, S b, qbitsize idx){
  if( b != 0 ) b = 1;
  a -= (a & (1<<idx));
  a += (b << idx);
}

S bitsubset(S a, const std::vector<qbitsize> & mask){
  S b = 0;
  for(std::size_t i = 0; i < mask.size(); i++){
    b += bitat(a, mask[i]) << i;
  }
  return b;
}

S bitsubset_set(S a, S b, const std::vector<qbitsize> & mask){
  for(std::size_t i = 0; i < mask.size(); i++){
    bitsetat(a, (b >> i) & 1, mask[i]);
  }
  return a;
}

std::string bit_to_string(S a, qbitsize qbit_n){
  std::string s = "";
  for(qbitsize i = 0; i < qbit_n; i++){
    s += std::to_string(bitat(a, i));
  }
  return s;
}
#endif
