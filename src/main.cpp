#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <stdexcept>
#include "qcparser/parser.hpp"
#include "qcparser/interpreter.hpp"

void interactive_mode();
void file_mode(const std::string & filename);

int main(int argc, char* argv[]){
  if( argc == 0 ){
    interactive_mode();
  }else if( argc == 1 ){
    std::string filename = argv[1];
    file_mode();
  }else if( argc != 0 ){
    std::cout << "QCirS" << std::endl;
    std::cout << "USAGE : " << std::endl;
    std::cout << "    qcirs <input>      run <input>" << std::endl;
    std::cout << "    qcirs              interactive mode" << std::endl;
  }
  return 0;
}

void file_mode(const std::string & filename){
  std::ifstream fin;
  fin.open(filename, std::ios::in);
  if( !fin ){
    std::cout << "error : cannot open file " << filename << "." << std::endl;
    exit(1);
  }
  while(std::getline(fin, source)){
    qcparser::env e;
    std::string source;
    while(std::getline(fin, source)){
      try{
        qcparser::program program = qcparser::parse(source);
        qcparser::interpret(program, e);
      }catch(const std::string & s){
        std::cout << s << std::endl;
        exit(1);
      }catch(std::exception & e){
        std::cout << "ERROR : " << e.what() << std::endl;
        exit(1);
      }
    }
  }
  fin.close();
}

void print_logo();
void interactive_mode(){
  print_logo();

  qcparser::env e;
  e.interactive = true;

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
