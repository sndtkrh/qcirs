#ifndef QGATEU
#define QGATEU

Qcircuit::QgateU::QgateU( Qcircuit * qc,
    const UnitaryMat * U,
    const std::vector<qbitsize> & operand )
    : U(U), operand(operand) {
  set_qc(qc);
  std::size_t matsize = ( 1 << operand.size() );
  assert( matsize == U->size() );
  for(qbitsize q_idx : operand ){
    assert( q_idx < get_qc().get_qbit_n() );
  }
  assert( no_duplication( operand ) );
}

void Qcircuit::QgateU::act(){
  Qstate newstate( get_qc().state.size(), 0);
  for(std::size_t s = 0; s < get_qc().state.size(); s++){
    comp coeff = get_qc().state[s];
    std::size_t e = bitsubset(s, operand);
    Vec v( 1 << operand.size(), 0 );
    v[e] = 1;
    v = (*U) * v;
    for(std::size_t subt = 0; subt < (1 << operand.size()); subt++){
      std::size_t t = bitsubset_set(s, subt, operand);
      newstate[t] += coeff * v[subt];
    }
  }
  get_qc().state = newstate;
}
#endif
