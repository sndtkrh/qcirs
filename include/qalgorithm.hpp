#include "common.hpp"
#include "qcircuit.hpp"
#include "matrices.hpp"

void qparallel(Qcircuit & qc, const std::function<bool(std::size_t)> & f){
  qbitsize qbit_n = qc.get_qbit_n();
  std::vector<qbitsize> controller(qbit_n - 1);
  for(qbitsize i = 0; i < controller.size(); i++){
    controller[i] = i;
  }
  qc.add_qgate_qmux(f, controller, qbit_n - 1);
}

void deutsch_jozsa(Qcircuit & qc, std::function<bool(std::size_t)> f){
  qbitsize qbit_n = qc.get_qbit_n();
  qc.state_at(0) = 0;
  qc.state_at(1 << (qbit_n - 1)) = 1; // let state be |0...01>.
  for(qbitsize i = 0; i < qbit_n; i++){ // H^{⊗qbit_n}
    qc.add_qgate_u(&H, {i});
  }
  qparallel(qc, f);
  for(qbitsize i = 0; i < qbit_n - 1; i++){ // H^{⊗qbit_n-1}
    qc.add_qgate_u(&H, {i});
  }
}
