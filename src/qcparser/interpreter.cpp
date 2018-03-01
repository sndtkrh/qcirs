#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "qc/qcore.hpp"
#include "qcparser/parser.hpp"
#include "qcparser/interpreter.hpp"

namespace qcparser {

  env::env(){
    interactive = false;
    measure_way = random;
    measure_printpr = false;
    um["H"] = &qc::H;
    um["X"] = &qc::PauliX;
    um["Y"] = &qc::PauliY;
    um["Z"] = &qc::PauliZ;
    um["CNOT"] = &qc::CNOT;
  }
  env::~env(){
    for(auto & q : qc){
      delete q.second;
    }
  }

  // interpret command
  run_command::run_command(env * e_) : e_(e_) { }
  // define @<qc_indicator> <qbit_n>
  void run_command::operator()(define & c) const {
    if( exist_qc(c.qc_indicator) ){
      throw "error : @" + c.qc_indicator + " is already defined.";
    }else{
      e_->qc[c.qc_indicator] = new qc::Qcircuit(c.qbit_n);
      long long qbit_n = c.qbit_n;
      if( e_->interactive ){
        std::cout << "defined quantum circuit : "
          << "@" << c.qc_indicator << " of "
          << qbit_n << " q-bits" << std::endl;
      }
    }
  }
  // measure @<qc_indicator> <qbit_indicator>
  void run_command::operator()(measure & c) const {
    if( exist_qc(c.qc_indicator) ){
      qc::Qcircuit & qc = *(e_->qc[c.qc_indicator]);
      std::vector<double> result;
      if( e_->measure_way == deterministic ){
        result = qc.measure_change_state_deterministically(c.qbit_indicator);
      }else{ // e_->measure_way == random
        result = qc.measure_change_state_randomly(c.qbit_indicator);
      }
      if( e_->measure_printpr ){
        std::size_t i = 0;
        for(double p : result ){
          std::cout
            << "Probability["
            << qc::bit_to_string(i, c.qbit_indicator.size())
            << "] = " << p << std::endl;
          i++;
        }
      }
    }else{
      throw "error : @" + c.qc_indicator + " is not defined.";
    }
  }
  // print @<qc_indicator>
  void run_command::operator()(print & c) const {
    if( exist_qc(c.qc_indicator) ){
      qc::Qcircuit & qc = *(e_->qc[c.qc_indicator]);
      std::cout << qc::state_to_string(qc.get_state(), qc.get_qbit_n()) << std::endl;
    }else{
      throw "error : @" + c.qc_indicator + " is not defined.";
    }
  }
  // add @<qc_indicator> <qgates>
  void run_command::operator()(add & c) const {
    if( exist_qc(c.qc_indicator) ){
      qc::Qcircuit & qc = *(e_->qc[c.qc_indicator]);
      int um_n = c.qgates.size();
      for(qgate & qg : c.qgates){
        if( ! exist_um(qg.unitary_mat_indicator) ){
          throw "error : Unitary matrix " + qg.unitary_mat_indicator + " is not defined.";
          return;
        }
      }
      for(qgate & qg : c.qgates){
        qc.add_qgate_u(e_->um[qg.unitary_mat_indicator], qg.qbit_indicator);
      }
      qc.run();
      for(qc::qbitsize i = 0; i < um_n; i++){
        qc.pop_back_qgate();
      }
      if( e_->interactive ){
        std::cout << "added unitary matrix" << std::endl;
      }
    }else{
      throw "error : @" + c.qc_indicator + " is not defined.";
    }
  }

  bool run_command::exist_qc(std::string & qc_indicator) const {
    return (e_->qc.find(qc_indicator) != e_->qc.end() );
  }
  bool run_command::exist_um(std::string & unitary_mat_indicator) const {
    return e_->um.find(unitary_mat_indicator) != e_->um.end();
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
