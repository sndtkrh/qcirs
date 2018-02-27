#include "qc/qcircuit.hpp"

Qcircuit::Qgate::~Qgate(){}
void Qcircuit::Qgate::set_qc(Qcircuit * qc_){
  qc = qc_;
}
Qcircuit & Qcircuit::Qgate::get_qc() const {
  return *qc;
}
