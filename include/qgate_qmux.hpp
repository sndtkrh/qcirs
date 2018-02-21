#ifndef QGATEQMUX
#define QGATEQMUX
#include "qcircuit.hpp"

Qcircuit::QgateQMUX::QgateQMUX( Qcircuit * qc,
    const std::vector<const UnitaryMat *> & Us,
    const std::vector<qbitsize> & controller,
    const std::vector<qbitsize> & operand)
    : Us(Us), controller(controller), operand(operand) {
  set_qc(qc);
  assert( Us.size() == (1 << controller.size()) );
  for(const UnitaryMat * U : Us){
    assert( U->size() == (1 << operand.size()) );
  }
  assert( no_duplication(controller) );
  assert( no_duplication(operand) );
}

void Qcircuit::QgateQMUX::act(){
  Qstate newstate( get_qc().state.size(), 0);
  for(std::size_t s = 0; s < get_qc().state.size(); s++){
    comp coeff = get_qc().state[s];
    std::size_t c = bitsubset(s, controller);
    std::size_t e = bitsubset(s, operand);
    Vec v( 1 << operand.size(), 0 );
    v[e] = 1;
    v = (*Us[c]) * v;
    for(std::size_t subt = 0; subt < (1 << operand.size()); subt++){
      std::size_t t = bitsubset_set(s, subt, operand);
      newstate[t] += coeff * v[subt];
    }
  }
  get_qc().state = newstate;
}
#endif
