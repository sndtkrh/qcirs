#ifndef BITOP
#define BITOP
namespace qc {
  typedef std::size_t S;

  S bitat(S a, qbitsize idx);
  void bitsetat(S & a, S b, qbitsize idx);
  S bitsubset(S a, const std::vector<qbitsize> & mask);
  S bitsubset_set(S a, S b, const std::vector<qbitsize> & mask);
  std::string bit_to_string(S a, qbitsize qbit_n);
}
#endif
