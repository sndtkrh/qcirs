#include <string>
#include <vector>
#include "qc/qcore.hpp"
#include "qcparser/parser.hpp"
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

namespace qcparser {
  program parse(std::string source) {
    typedef std::string::const_iterator It;
    qcparser::grammar<It> grammar;
    It first = source.begin(), last = source.end();
    qcparser::program result;
    bool success = qi::phrase_parse(first, last, grammar, qi::ascii::space, result);
    if( success && first == last ){
      return result;
    }else{
      throw std::string("invalid syntax");
    }
  }
}
