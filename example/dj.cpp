/* This is an implementation of Deutsch-Jozsa algorithm */
#include <iostream>
#include <qc/qcore.hpp>
const double eps = 1e-9;

bool dj_algorithm(qc::Qcircuit & qcircuit,
    const std::function<bool(std::size_t)> & f){
  qc::qbitsize qbit_n = qcircuit.get_qbit_n();
  // Let the state be $\ket{0 \dots 0 1}$.
  qcircuit.state_at(0) = 0;
  qcircuit.state_at(1 << (qbit_n - 1)) = 1;
  for(qc::qbitsize i = 0; i < qbit_n; i++){ // $H^{\otimes \mathtt{qbit\_n}}$
    qcircuit.add_qgate_u(&qc::H, {i});
  }
  qc::qparallel(qcircuit, f); // Add the quantum oracle.
  for(qc::qbitsize i = 0; i < qbit_n - 1; i++){ // $H^{\otimes \mathtt{qbit\_n} - 1}$
    qcircuit.add_qgate_u(&qc::H, {i});
  }
  qcircuit.run();
  // measure $q_0 q_1$ by computational basis $\{\ket{00}, \ket{01}, \ket{10}, \ket{11}\}$
  auto pr = qcircuit.measure({0, 1});
  bool res = (pr[0] >= 1.0 - eps) ? true : false;
  // print the result
  std::cout << "The probability of results of measurement is [ ";
  for(auto p : pr){ std::cout << p << " "; }
  std::cout << "]." << std::endl;
  for(int i = 0; i < 8; i++){
    std::cout << qcircuit.state_at(i) << std::endl;
  }
  std::cout
    << "This function is " << (res ? "constant." : "balanced.")
    << std::endl;
  std::cout << std::endl;

  return res;
}

int main(){
  // quantum circuits with 3-qbit
  qc::Qcircuit qc_c(2 + 1), qc_b(2 + 1);
  /*
  * Consider following functions as $f : \{0,1\}^2 \to \{\true, \false\}$.
  * Regard the argument std::size_t a
  * as the element of $\{0,1\}^2$ by its bit pattern.
  */
  // constant function
  auto f_const = [](std::size_t a) { return true; };
  // balanced function
  auto f_balanced = [](std::size_t a) { return (a < 2); };

  bool res;
  std::cout
    << "Result of applying D-J algorithm to a constant function:"
    << std::endl;
  res = dj_algorithm(qc_c, f_const);

  std::cout
    << "Result of applying D-J algorithm to a balanced function:"
    << std::endl;
  res = dj_algorithm(qc_b, f_balanced);
}
