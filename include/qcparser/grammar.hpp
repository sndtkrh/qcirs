#ifndef GRAMMAR
#define GRAMMAR
#include <string>
#include <vector>
#include <boost/spirit/include/qi.hpp>
#include "qcparser/command.hpp"
#include "qcparser/program.hpp"

namespace qcparser {
  template <typename Iterator>
  struct grammar : boost::spirit::qi::grammar<Iterator, qcparser::program(), boost::spirit::ascii::space_type> {
    grammar();
    boost::spirit::qi::rule<Iterator, qcparser::program(), boost::spirit::ascii::space_type> program;
    boost::spirit::qi::rule<Iterator, qcparser::command(), boost::spirit::ascii::space_type> command;
    boost::spirit::qi::rule<Iterator, qcparser::define(), boost::spirit::ascii::space_type> c_define;
    boost::spirit::qi::rule<Iterator, qcparser::measure(), boost::spirit::ascii::space_type> c_measure;
    boost::spirit::qi::rule<Iterator, qcparser::print(), boost::spirit::ascii::space_type> c_print;
    boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> qc_indicator;
    boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> qc_name;
    boost::spirit::qi::rule<Iterator, std::vector<int>(), boost::spirit::ascii::space_type> qbit_indicator;
    boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> comment;
    boost::spirit::qi::rule<Iterator, std::string(), boost::spirit::ascii::space_type> comment_text;
  };

  template <typename Iterator>
  grammar<Iterator>::grammar() : grammar::base_type(program) {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    program %= *(command | comment);
    command %= (c_define | c_measure | c_print);

    c_define
      %= qi::lit("define")
        >> qc_indicator
        >> qi::int_;
    c_measure
      %= qi::lit("measure")
        >> qc_indicator
        >> qbit_indicator;
    c_print
      %= qi::lit("print")
        >> qc_indicator;

    qc_indicator
      %= qi::lit("@")
        >> qc_name;
    qc_name
      %= qi::lexeme[+(qi::alpha)];
    qbit_indicator
      %= qi::lit("{")
        >> qi::int_ % ','
        >> qi::lit("}");

    comment
      %= qi::lit("--")
        >> comment_text;
    comment_text
      %= qi::lexeme[*(qi::char_ - '\n' - '\r')];
  }
}
#endif
