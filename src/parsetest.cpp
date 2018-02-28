#include <qcparser/command.hpp>
#include <qcparser/grammar.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

struct printer : boost::static_visitor<void> {
  void operator()(qcparser::define &) const{
    std::cout << "measure" << std::endl;
  }
  void operator()(qcparser::measure &) const {
    std::cout << "define" << std::endl;
  }
  void operator()(qcparser::print &) const {
    std::cout << "print" << std::endl;
  }
};

void parsetest(){
  std::string s_comment("-- this is a comment");
  std::string s_measure("measure @hoge {0,1,2}");
  std::string s_define("define @foo {0}");
  std::string s_print("print @hoo");
  std::string s = s_print;
  qcparser::command result;
  QCgrammar<std::string::const_iterator> grammar;
  std::string::const_iterator first = s.begin(), last = s.end();
  bool success = qi::phrase_parse(first, last, grammar, qi::ascii::space, result);
  if( success && first == last ) {
    std::cout << "success " << std::endl;
    boost::apply_visitor(printer(), result);
  }else{
    std::cout << "invalid syntax" << std::endl;
  }
}
