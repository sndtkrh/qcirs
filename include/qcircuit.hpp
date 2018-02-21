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
  ~Qcircuit(){
    for( Qgate * qg : qgate ){
      delete qg;
    }
  }
  void add_qgate_u(const UnitaryMat & U, const std::vector<qbitsize> & operand ){
    qgate.push_back( new QgateU(this, U, operand) );
  }
  void add_qgate_qmux(const std::vector<UnitaryMat> & Us,
      const std::vector<qbitsize> & controller,
      const std::vector<qbitsize> & operand){
    qgate.push_back( new QgateQMUX(this, Us, controller, operand) );
  }
  qbitsize get_qbit_n() const {
    return qbit_n;
  }
  const Qstate & get_state() const {
    return state;
  }
  void set_state(const Qstate & s){
    assert( state.size() == s.size() );
    state = s;
  }
  comp & state_at(std::size_t q_idx){
    assert( q_idx < state.size() );
    return state[q_idx];
  }
  void run(){
    for(Qgate * qg : qgate){
      qg->act();
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
  Qstate get_most_likely_state_after_measurement(
      std::vector<qbitsize> computational_basis ){
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
  class Qgate{
  public:
    virtual ~Qgate(){}
    void set_qc(Qcircuit * qc_){
      qc = qc_;
    }
    Qcircuit & get_qc() const {
      return *qc;
    }
    virtual void act() = 0;
  private:
    Qcircuit * qc;
  };

  std::vector<Qgate * > qgate;

  class QgateU : public Qgate {
  public:
    QgateU(){}
    QgateU( Qcircuit * qc, const UnitaryMat & U, const std::vector<qbitsize> & operand );
    void act();
  private:
    UnitaryMat U;
    std::vector<qbitsize> operand;
  };
  class QgateQMUX : public Qgate { // quantum multiplexer
  public:
    QgateQMUX(){}
    QgateQMUX( Qcircuit * qc,
              const std::vector<UnitaryMat> & Us,
              const std::vector<qbitsize> & controller,
              const std::vector<qbitsize> & operand);
    void act();
  private:
    std::vector<UnitaryMat> Us;
    std::vector<qbitsize> controller;
    std::vector<qbitsize> operand;
  };
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