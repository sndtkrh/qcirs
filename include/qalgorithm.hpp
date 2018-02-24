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

/*
* apply Grover rotation to qc's head_n q-bits from head.
* Grover rotation G is equal to (2|ψ><ψ| - I)O,
* whire O is quantum oracle and |ψ> = 1 / √(2^n) Σ |x>.
*/
void grover_rotation(Qcircuit & qc,
    qbitsize head_n,
    std::function<Qstate(Qstate &)> & qoracle){
  // add qoracle
  qc.add_qgate_custom( qoracle );

  // H^{⊗head_n}
  for(qbitsize i = 0; i < head_n; i++){
    qc.add_qgate_u(&H, {i});
  }

  /*
  * conditinal phase shift
  * |0...0>|φ> → |0...0>|φ>
  * |x>|φ> → -|x>|φ> (x != 0...0)
  */
  qc.add_qgate_custom( [head_n](Qstate & state) {
    Qstate newstate(state.size(), 0);
    for(std::size_t i = 0; i < state.size(); i++){
      if( (i & ((1 << head_n) - 1)) == 0 ){
        newstate[i] += state[i];
      }else{
        newstate[i] += -state[i];
      }
    }
    return newstate;
  } );
  // H^{⊗head_n}
  for(qbitsize i = 0; i < head_n; i++){
    qc.add_qgate_u(&H, {i});
  }
}

/*
* Grover's search algorithm
* - O(√N) time where N = 2^n, N is total data size.
* - Pr(success) = Θ(1)
* - χ : {0,1,2,...,N-1} → Bool
*/
void grover_search(Qcircuit & qc,
    const std::function<bool(std::size_t)> & chi,
    std::size_t sol_n){
  /*
  * chi χ is a function such that
  * χ(x) = true  (x is a key which we search for),
  *        = false (otherwise),
  * and it satisfies that
  * #{x | chi(x) = true} = sol_n.
  */

  const double eps = 1e-10;
  qbitsize qbit_n = qc.get_qbit_n();
  qbitsize dn = qbit_n - 1;
  std::size_t N = (1 << dn); // data size

  // cos (θ/2) = sqrt((N - sol_n) / N)
  double theta = std::acos( std::sqrt((N - sol_n) * 1.0 / N) ) * 2;
  double phi = std::acos( std::sqrt(sol_n * 1.0 / N) ) / theta;
  std::size_t fl = std::floor(phi) + eps;
  std::size_t cl = std::ceil(phi) + eps;
  double df = abs( phi - fl );
  double dc = abs( phi - cl );
  std::size_t k = (df < dc) ? fl : cl; // k is an integer nearest to phi.

  /*
  * qoracle is defined by
  * qoracle|x,q> = U_chi|x,q> = |x>|q⊕chi(x)>
  * where ⊕ is addition mod 2.
  */
  std::function<Qstate(Qstate &)> qoracle = [&chi, qbit_n, dn](Qstate & state) {
    Qstate newstate(state.size(), 0);
    for(std::size_t s = 0; s < state.size(); s++){
      std::size_t q = s & (1 << dn); // get a tail qbit
      std::size_t x = s & ((1 << dn) - 1); // get dn q-bits from head
      if(chi(x)){
        newstate[x + (q ^ (1 << dn))] += state[s];
      }else{
        newstate[s] = state[s];
      }
    }
    return newstate;
  };

  // let state be |0...01>.
  qc.state_at(0) = 0;
  qc.state_at(1 << (qbit_n - 1)) = 1;

  for(qbitsize i = 0; i < qbit_n; i++){ // H^{⊗qbit_n}
    qc.add_qgate_u(&H, {i});
  }

  // add Grover rotations G^k
  for(std::size_t i = 0; i < k; i++){
    grover_rotation(qc, qbit_n - 1, qoracle);
  }
}
