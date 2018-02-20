#ifndef QGATE
#define QGATE
#include "qcircuit.hpp"

Qcircuit::Qgate::Qgate( Qcircuit * qc, const UnitaryMat & U, const std::vector<qbitsize> & operand ) : qc(qc), U(U), operand(operand) {
  long long matsize = ( 1 << operand.size() );
  assert( matsize == U.size() );
  for(qbitsize q_idx : operand ){
    assert( q_idx < qc->get_qbit_n() );
  }
  assert( no_duplication( operand ) );
}

void Qcircuit::Qgate::act(){
  Qstate newstate( qc->state.size(), 0);
  for(std::size_t s = 0; s < qc->state.size(); s++){
    comp coeff = qc->state[s];
    std::size_t idx = 0;
    Vec v( 1 << operand.size(), 0 );
    std::size_t e = 0;
    e += bitsubset(s, operand);
    v[e] = 1;
    v = U * v;
    for(std::size_t subt = 0; subt < (1 << operand.size()); subt++){
      std::size_t t = bitsubset_set(s, subt, operand);
      newstate[t] += coeff * v[subt];
    }
  }
  qc->state = newstate;
}

#endif
