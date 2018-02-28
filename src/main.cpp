#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include "qcparser/parser.hpp"
#include "qcparser/interpreter.hpp"

int main(){
  qcparser::env e;
  std::string source;
  std::cout << ">> " << std::flush;
  while(std::getline(std::cin, source)){
    try{
      qcparser::program program = qcparser::parse(source);
      qcparser::interpret(program, e);
    }catch(const std::string & s){
      std::cout << s << std::endl;
    }catch(std::exception & e){
      std::cout << "ERROR : " << e.what() << std::endl;
    }
    std::cout << ">> " << std::flush;
  }
  std::cout << std::endl;
}
