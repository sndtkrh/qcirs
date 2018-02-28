#include <iostream>
#include <iterator>
#include "qcparser/parser.hpp"

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

  std::cout << "input = \"" << s << "\"" << std::endl;
  qcparser::program result = qcparser::parse(s);
  for(auto & r : result){
    boost::apply_visitor(program_printer(), r);
  }
}
