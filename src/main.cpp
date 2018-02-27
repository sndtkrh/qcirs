#include <iostream>
#include <vector>
#include "qc/qcore.hpp"

using namespace std;

void test_grover_rotation();
void test_grover_search();
void test_qft();
void test_deutch_jozsa();
void test_qmux();
void show_probability(const vector<double> & p, qbitsize qbit_n);

int main(){
  //test_grover_rotation();
  test_grover_search();
  //test_qft();
  //test_deutch_jozsa();
  //test_qmux();
}
void test_grover_rotation(){
  auto f = [](std::size_t key){
    return key == 0;
  };
  std::function<Qstate(Qstate &)> qoracle = [&f](Qstate & state) {
    Qstate newstate(state.size());
    for(std::size_t s = 0; s < state.size(); s++){
      std::size_t data = s & (state.size() / 2 - 1); // get data register from s
      if( f(data) ){
        std::size_t t = s;
        if( t == data ){
          // result register is 0
          t += state.size() / 2;
        }else{
          // result register is 1
          // nothing to do
        }
        newstate[t] = state[s];
      }else{
        newstate[s] = state[s];
      }
    }
    return newstate;
  };
  Qcircuit qc(3 + 1);
  Qstate state;
  grover_rotation(qc, 3, qoracle);
  qc.set_state({0.707106782373095,0,0,0,0,0,0,0,0.707106782373095,0,0,0,0,0,0,0});
  cout << state_to_string(qc.get_state(), 4) << endl;
  qc.run();
  cout << state_to_string(qc.get_state(), 4) << endl;
  show_probability( qc.measure({0,1,2}), 3 );

  cout << "State of the quantum circuit after measurement is" << endl;
  state = qc.get_most_likely_state_after_measurement({0,1,2});
  cout << state_to_string(state, 4) << endl;
}
void test_grover_search(){
  auto f = [](std::size_t key){
    return key == 1;
  };
  Qcircuit qc(3 + 1);
  Qstate state;
  grover_search(qc, f, 1);
  cout << state_to_string(qc.get_state(), 4) << endl;
  qc.run();
  cout << state_to_string(qc.get_state(), 4) << endl;
  show_probability( qc.measure({0,1,2}), 3 );

  cout << "State of the quantum circuit after measurement is" << endl;
  state = qc.get_most_likely_state_after_measurement({0,1,2});
  cout << state_to_string(state, 4) << endl;
}
void test_qft(){
  MatrixGenerator mg;
  UnitaryMat * p = mg.get_qft(3);
  cout << to_string(*p) << endl;
}
void test_qmux(){
  Qcircuit qc(2);
  cout << "CNOT gate by QMUX" << endl;
  qc.add_qgate_qmux({&I_2, &PauliX}, {1}, {0});
  qc.set_state({1,0,0,0});
  qc.run();
  cout << state_to_string(qc.get_state(), 2) << endl;
  qc.set_state({0,1,0,0});
  qc.run();
  cout << state_to_string(qc.get_state(), 2) << endl;
  qc.set_state({0,0,1,0});
  qc.run();
  cout << state_to_string(qc.get_state(), 2) << endl;
  qc.set_state({0,0,0,1});
  qc.run();
  cout << state_to_string(qc.get_state(), 2) << endl;
}
void test_deutch_jozsa(){
  function<bool(size_t)> f_const = [](size_t){ return true; };
  function<bool(size_t)> f_balanced = [](size_t a){ return (a % 2 == 0); };
  Qcircuit qc(2 + 1);
  deutsch_jozsa(qc, f_balanced);
  Qstate state;

  cout << "Initial state of the quantum circuit is" << endl;
  state = qc.get_state();
  cout << state_to_string(state, 3) << endl;
  qc.run();

  cout << "State of the quantum circuit after unitary transformations is" << endl;
  state = qc.get_state();
  cout << state_to_string(state, 3) << endl;

  show_probability( qc.measure({0,1}), 2 );

  cout << "State of the quantum circuit after measurement is" << endl;
  state = qc.get_most_likely_state_after_measurement({0,1});
  cout << state_to_string(state, 3) << endl;
}

void show_probability(const vector<double> & p, qbitsize qbit_n){
  std::size_t i = 0;
  for(double a : p ){
    cout << "Probability of " << bit_to_string(i, qbit_n) << " = " << a << endl;
    i++;
  }
  cout << endl;
}
