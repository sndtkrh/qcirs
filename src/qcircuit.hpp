#ifndef QCIRCUIT
#define QCIRCUIT
#include "common.hpp"
#include "bitoperation.hpp"
typedef std::vector<comp> Qstate;
bool no_duplication( const std::vector<qbitsize> & v );

class Qcircuit {
public:
  Qcircuit( qbitsize qbit_n ) : qbit_n( qbit_n ) {
    state.resize( 1 << qbit_n, 0 );
    state[0] = 1; // initialize state to |0...0>
  }
  void add_qgate(const UnitaryMat & U, const std::vector<qbitsize> & operand ){
    qgate.emplace_back(this, U, operand);
  }
  qbitsize get_qbit_n(){
    return qbit_n;
  }
  const Qstate & get_state() const {
    return state;
  }
  comp & state_at(std::size_t q_idx){
    assert( q_idx < state.size() );
    return state[q_idx];
  }
  void run(){
    for(Qgate & g : qgate){
      g.act();
    }
  }
  std::vector<double> measure(std::vector<qbitsize> computational_basis){
    qbitsize n = computational_basis.size();
    assert( no_duplication( computational_basis ) );
    std::vector<double> probability( 1 << n, 0 );
    for(std::size_t i = 0; i < (1 << qbit_n); i++){
      std::size_t base = bitsubset( i, computational_basis );
      probability[base] += abs(state[i]) * abs(state[i]);
    }
    return probability;
  }
  Qstate get_most_likely_state_after_measurement(std::vector<qbitsize> computational_basis){
    std::vector<double> pr = measure( computational_basis );
    double p = 0;
    std::size_t k;
    for(std::size_t i = 0; i < pr.size(); i++){
      if( pr[i] > p ){
        p = pr[i];
        k = i;
      }
    }
    Qstate likelystate( state.size(), 0 );
    for(std::size_t s = 0; s < state.size(); s++){
      if( bitsubset(s, computational_basis) == k ){
        likelystate[s] = state[s] / sqrt(p);
      }
    }
    return likelystate;
  }

private:
  qbitsize qbit_n;
  Qstate state;

  class Qgate {
  public:
    Qgate(){}
    Qgate( Qcircuit * qc, const UnitaryMat & U, const std::vector<qbitsize> & operand ) : qc(qc), U(U), operand(operand) {
      long long matsize = ( 1 << operand.size() );
      assert( matsize == U.size() );
      for(qbitsize q_idx : operand ){
        assert( q_idx < qc->get_qbit_n() );
      }
      assert( no_duplication( operand ) );
    }
    void act(){
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
  private:
    Qcircuit * qc;
    UnitaryMat U;
    std::vector<qbitsize> operand;
  };

  std::vector<Qgate> qgate;
};

std::string state_to_string(Vec a, qbitsize qbit_n){
  assert( a.size() == (1 << qbit_n) );
  std::string s = "";
  for(std::size_t i = 0; i < a.size(); i++){
    s += to_string(a[i]) + "|" + bit_to_string(i, qbit_n) + ">\n";
  }
  return s;
}

bool no_duplication( const std::vector<qbitsize> & v ){
  std::set<qbitsize> S;
  for( qbitsize e : v ){
    S.insert( e );
  }
  return v.size() == S.size();
}
#endif
