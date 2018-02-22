#ifndef QGATECUSTOM
#define QGATECUSTOM
#include "qcircuit.hpp"

Qgate::QgateCustom::QgateCustom( Qcircuit * qc, std::function<Qstate(Qstate &)> & f_ ){
  set_qc(qc);
  f = f_;
}

void Qgate::QgateCustom::act(){
  get_qc().state = f( get_qc().state );
}
#endif
