#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "qc/qcore.hpp"
#include "qcparser/parser.hpp"
#include "qcparser/interpreter.hpp"

namespace qcparser {

  env::env(){
    um["H"] = &H;
    um["X"] = &PauliX;
    um["Y"] = &PauliY;
    um["Z"] = &PauliZ;
    um["CNOT"] = &CNOT;
  }
  env::~env(){
    for(auto & q : qc){
      delete q.second;
    }
  }

  // interpret command
  run_command::run_command(env * e_) : e_(e_) { }
  void run_command::operator()(define & c) const {
    e_->qc[c.qc_indicator] = new Qcircuit(c.qbit_n);
    std::cout << "defined quantum circuit : @" << c.qc_indicator << std::endl;
  }
  void run_command::operator()(measure & c) const {
    if( exist_qc(c.qc_indicator) ){
      Qcircuit & qc = *(e_->qc[c.qc_indicator]);
      std::vector<double> result = qc.measure(c.qbit_indicator);
      std::size_t i = 0;
      for(double p : result ){
        std::cout
          << "Probability["
          << bit_to_string(i, c.qbit_indicator.size())
          << "] = " << p << std::endl;
        i++;
      }
    }
  }
  void run_command::operator()(print & c) const {
    if( exist_qc(c.qc_indicator) ){
      Qcircuit & qc = *(e_->qc[c.qc_indicator]);
      std::cout << state_to_string(qc.get_state(), qc.get_qbit_n()) << std::endl;
    }
  }
  void run_command::operator()(add & c) const {
    if( exist_qc(c.qc_indicator) ){
      Qcircuit & qc = *(e_->qc[c.qc_indicator]);
      int um_n = c.qgates.size();
      for(qgate & qg : c.qgates){
        if( ! exist_um(qg.unitary_mat_indicator) ){
          return;
        }
      }
      for(qgate & qg : c.qgates){
        qc.add_qgate_u(e_->um[qg.unitary_mat_indicator], qg.qbit_indicator);
      }
      qc.run();
      for(qbitsize i = 0; i < um_n; i++){
        qc.pop_back_qgate();
      }
      std::cout << "added" << std::endl;
    }
  }

  bool run_command::exist_qc(std::string & qc_indicator) const {
    if( e_->qc.find(qc_indicator) == e_->qc.end() ) {
      std::cout
      << "error : Quantum circuit @"
      << qc_indicator
      << " is not defined." << std::endl;
      return false;
    }else{
      return true;
    }
  }
  bool run_command::exist_um(std::string & unitary_mat_indicator) const {
    if( e_->um.find(unitary_mat_indicator) == e_->um.end() ) {
      std::cout
      << "error : Unitary matrix "
      << unitary_mat_indicator
      << " is not defined." << std::endl;
      return false;
    }else{
      return true;
    }
  }

  // interpret program
  run_program::run_program(env * e_) : e_(e_) { }
  void run_program::operator()(std::string &) const { }
  void run_program::operator()(command & c) const {
    boost::apply_visitor(run_command(e_), c);
  }

  // call this function to use interpreter
  void interpret(program p, env & e){
    for(auto & c : p){
      boost::apply_visitor(run_program(&e), c);
    }
  }
}