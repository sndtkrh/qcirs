#include "qc/matrices.hpp"

const UnitaryMat I_2({
  {1,0},
  {0,1} });
const UnitaryMat PauliX({
  {0,1},
  {1,0} });
const UnitaryMat PauliY({
  {0, comp(0,-1)},
  {comp(0,1), 0} });
const UnitaryMat PauliZ({
  {1,0},
  {0,-1} });
static const double sqrt2 = std::sqrt(2.0);
const UnitaryMat H( {
  {1/sqrt2, 1/sqrt2 },
  {1/sqrt2, -1/sqrt2}, });
const UnitaryMat CNOT( {
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 0, 1},
  {0, 0, 1, 0} });

const Vec v_zero = {1, 0};
const Vec v_one = {0, 1};
const Vec v_plus = {1/sqrt2, 1/sqrt2};
const Vec v_minus = {1/sqrt2, -1/sqrt2};
