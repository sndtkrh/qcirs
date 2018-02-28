#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include "qcparser/parser.hpp"
#include "qcparser/interpreter.hpp"

void print_logo(){
  const std::string logo ="\
  _____    _____   _         ____     \n\
 / ___ \\  /  ___\\ ( )  _  _ (  __\\ \n\
( (_,_) )(  (____ | | | |'/__\\ \\    \n\
 \\___  /  \\_____/ |_| |_|  \\____)  \n\
     \\_\\                            \n\
";
std::cout << logo << std::flush;
std::cout << "QCirS -- Quantum Circuit Simulator" << std::endl;
std::cout << "==================================" << std::endl;
std::cout << std::endl;
}

int main(){
  print_logo();
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
