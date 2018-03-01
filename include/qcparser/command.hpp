#ifndef QCCOM
#define QCCOM

namespace qcparser{

  struct define {
    std::string qc_indicator;
    qc::qbitsize qbit_n;
  };

  struct measure {
    std::string qc_indicator;
    std::vector<qc::qbitsize> qbit_indicator;
  };

  struct print {
    std::string qc_indicator;
  };

  struct qgate;
  struct add {
    std::string qc_indicator;
    std::vector<qgate> qgates;
  };

  struct qgate{
    std::string unitary_mat_indicator;
    std::vector<qc::qbitsize> qbit_indicator;
  };

  typedef boost::variant<define, measure, print, add> command;
}

BOOST_FUSION_ADAPT_STRUCT(
  qcparser::define,
  (std::string, qc_indicator)
  (qc::qbitsize, qbit_n)
)
BOOST_FUSION_ADAPT_STRUCT(
  qcparser::measure,
  (std::string, qc_indicator)
  (std::vector<qc::qbitsize>, qbit_indicator)
)
BOOST_FUSION_ADAPT_STRUCT(
  qcparser::print,
  (std::string, qc_indicator)
)
BOOST_FUSION_ADAPT_STRUCT(
  qcparser::qgate,
  (std::string, unitary_mat_indicator)
  (std::vector<qc::qbitsize>, qbit_indicator)
)
BOOST_FUSION_ADAPT_STRUCT(
  qcparser::add,
  (std::string, qc_indicator)
  (std::vector<qcparser::qgate>, qgates)
)
#endif
