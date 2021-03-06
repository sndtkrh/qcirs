#ifndef PARSER
#define PARSER
#include <vector>
#include <string>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>
#include "qc/qcore.hpp"
#include "command.hpp"
#include "program.hpp"
#include "grammar.hpp"
namespace qcparser{
  program parse(std::string);
}
#endif
