#include <iostream>
#include <qc/qcore.hpp>
const double eps = 1e-9;

bool dj_algorithm(qc::Qcircuit & qcircuit,
    const std::function<bool(std::size_t)> & f){
  qc::qbitsize qbit_n = qcircuit.get_qbit_n();
  qcircuit.state_at(0) = 0;
  qcircuit.state_at(1 << (qbit_n - 1)) = 1; // let state be |0...01>.
  for(qc::qbitsize i = 0; i < qbit_n; i++){ // H^{⊗qbit_n}
    qcircuit.add_qgate_u(&qc::H, {i});
  }
  qc::qparallel(qcircuit, f); // add a quantum oracle
  for(qc::qbitsize i = 0; i < qbit_n - 1; i++){ // H^{⊗qbit_n-1}
    qcircuit.add_qgate_u(&qc::H, {i});
  }

  qcircuit.run();

  // measure [q_0 q_1] by computational basis {|00>, |01>, |10>, |11>}
  auto pr = qcircuit.measure({0, 1});
  std::cout << "The probability of results of measurement is [ ";
  for(auto p : pr){ std::cout << p << " "; }
  std::cout << "]." << std::endl;

  if(pr[0] >= 1.0 - eps) return true; // constant
  return false; // balanced
}

int main(){
  bool res;
  qc::Qcircuit qc_c(2 + 1), qc_b(2 + 1); // quantum circuits with 3-qbit
  // consider following functions as f : {0,1}^2 -> {true, false}
  // regard the argument std::size_t a as the element of {0,1}^2 by its bit pattern
  auto f_const = [](std::size_t a) { return true; }; // constant function
  auto f_balanced = [](std::size_t a) { return (a < 2); }; // balanced function

  res = dj_algorithm(qc_c, f_const);
  std::cout << "Result of appling Deutsch-Jozsa algorithm to a constant function: " << std::endl;
  for(int i = 0; i < 8; i++){
    std::cout << qc_c.state_at(i) << std::endl;
  }
  std::cout << "This function is " << (res ? "constant" : "balanced") << "." << std::endl;
  std::cout << std::endl;

  res = dj_algorithm(qc_b, f_balanced);
  std::cout << "Result of appling Deutsch-Jozsa algorithm to a balanced function: " << std::endl;
  for(int i = 0; i < 8; i++){
    std::cout << qc_b.state_at(i) << std::endl;
  }
  std::cout << "This function is " << (res ? "constant" : "balanced") << "." << std::endl;
  std::cout << std::endl;
}
