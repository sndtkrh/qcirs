#include <iostream>
#include <vector>
#include "qcore.hpp"

using namespace std;

int main(){
  function<bool(size_t)> f_const = [](size_t a){ return true; };
  function<bool(size_t)> f_balanced = [](size_t a){ return (a % 2 == 0); };
  Qcircuit qc(2 + 1);
  deutsch_jozsa(qc, f_const);
  Qstate state;

  cout << "Initial state of the quantum circuit is" << endl;
  state = qc.get_state();
  cout << state_to_string(state, 3) << endl;
  qc.run();

  cout << "State of the quantum circuit after unitary transformations is" << endl;
  state = qc.get_state();
  cout << state_to_string(state, 3) << endl;

  vector<double> p = qc.measure({0,1});
  std::size_t i = 0;
  for(double a : p ){
    cout << "Probability of " << bit_to_string(i,2) << " = " << a << endl;
    i++;
  }
  cout << endl;

  cout << "State of the quantum circuit after measurement is" << endl;
  state = qc.get_most_likely_state_after_measurement({0,1});
  cout << state_to_string(state, 3) << endl;
}
