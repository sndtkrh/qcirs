#ifndef QCCOM
#define QCCOM
#include <vector>
#include <string>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>

namespace qcparser{

  struct define {
    std::string qc_indicator;
    int qbit_n;
  };

  struct measure {
    std::string qc_indicator;
    std::vector<int> qbit_indicator;
  };

  struct print {
    std::string qc_indicator;
  };

  typedef boost::variant<define, measure, print> command;
}

BOOST_FUSION_ADAPT_STRUCT(
  qcparser::define,
  (std::string, qc_indicator)
  (int, qbit_n)
)
BOOST_FUSION_ADAPT_STRUCT(
  qcparser::measure,
  (std::string, qc_indicator)
  (std::vector<int>, qbit_indicator)
)
BOOST_FUSION_ADAPT_STRUCT(
  qcparser::print,
  (std::string, qc_indicator)
)
#endif
