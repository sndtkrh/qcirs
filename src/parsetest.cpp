#include <iostream>
#include <iterator>
#include "qcparser/parser.hpp"

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

struct command_printer : boost::static_visitor<void> {
  void operator()(qcparser::define & c) const{
    std::cout << "define" << std::endl;
    std::cout << "  @" << c.qc_indicator << " " << c.qbit_n << std::endl;
  }
  void operator()(qcparser::measure & c) const {
    std::cout << "measure" << std::endl;
    std::cout << "  @" << c.qc_indicator << " ";
    std::cout << "{";
    for(auto a : c.qbit_indicator){
      std::cout << a << " ";
    }
    std::cout << "}" << std::endl;
  }
  void operator()(qcparser::print & c) const {
    std::cout << "print" << std::endl;
    std::cout << "  @" << c.qc_indicator << std::endl;
  }
};

struct program_printer : boost::static_visitor<void> {
  void operator()(std::string & p) const{
    std::cout << "comment=\"" << p << "\"" << std::endl;
  }
  void operator()(qcparser::command & c) const{
    boost::apply_visitor(command_printer(), c);
  }
};

void parsetest(){
  std::string s_comment("-- this is a comment");
  std::string s_define("define @foo 4 ");
  std::string s_measure("measure @foo {0,1,2}");
  std::string s_print("print @foo");
  std::string s_program = s_define + " " + s_comment + "\n" + s_measure + "\n" + s_print;
  std::string s = s_program;

  typedef std::string::const_iterator It;
  qcparser::grammar<It> grammar;
  It first = s.begin(), last = s.end();
  qcparser::program result;
  bool success = qi::phrase_parse(first, last, grammar, qi::ascii::space, result);

  std::cout << "input = \"" << s << "\"" << std::endl;
  if( success && first == last ) {
    std::cout << std::endl;
    std::cout << "success " << std::endl;
    for(auto & r : result){
      boost::apply_visitor(program_printer(), r);
    }
  }else{
    std::cout << "invalid syntax" << std::endl;
    It b = s.begin();
    std::cout << "stopped at \"" << s.substr(std::distance(b,first)) << "\"" << std::endl;
  }
}
