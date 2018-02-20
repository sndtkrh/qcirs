#include "common.hpp"
#include "Qcircuit.hpp"
#include "matrices.hpp"

void qparallel(Qcircuit & qc, std::function<bool(std::size_t)> f){
  qbitsize qbit_n = qc.get_qbit_n();
  std::vector<qbitsize> o(qbit_n);
  o[0] = qbit_n - 1;
  for(qbitsize i = 0; i < qbit_n - 1; i++) o[i + 1] = i;
  qc.add_qgate( get_U(f, qbit_n - 1),  o);
}

void deutsch_jozsa(Qcircuit & qc, std::function<bool(std::size_t)> f){
  qbitsize qbit_n = qc.get_qbit_n();
  qc.state_at(0) = 0;
  qc.state_at(1 << (qbit_n - 1)) = 1; // let state be |0...01>.
  for(qbitsize i = 0; i < qbit_n; i++){ // H^{⊗qbit_n}
    qc.add_qgate(H, {i});
  }
  qparallel(qc, f);
  for(qbitsize i = 0; i < qbit_n - 1; i++){ // H^{⊗qbit_n-1}
    qc.add_qgate(H, {i});
  }
}
