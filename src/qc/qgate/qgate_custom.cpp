#include "qc/common.hpp"
#include "qc/qcircuit.hpp"

namespace qc {
Qcircuit::QgateCustom::QgateCustom(){}
Qcircuit::QgateCustom::QgateCustom( Qcircuit * qc, const std::function<Qstate(Qstate &)> & f_ ){
  set_qc(qc);
  f = f_;
}
void Qcircuit::QgateCustom::act(){
  get_qc().state = f( get_qc().state );
}
}
