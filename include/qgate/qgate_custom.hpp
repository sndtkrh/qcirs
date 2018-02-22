#ifndef QGATECUSTOM
#define QGATECUSTOM

Qcircuit::QgateCustom::QgateCustom( Qcircuit * qc, std::function<Qstate(Qstate &)> & f_ ){
  set_qc(qc);
  f = f_;
}

void Qcircuit::QgateCustom::act(){
  get_qc().state = f( get_qc().state );
}
#endif
