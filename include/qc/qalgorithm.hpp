#ifndef QALG
#define QALG
#include "common.hpp"
#include "qcircuit.hpp"
#include "matrices.hpp"

void qparallel(Qcircuit & qc, const std::function<bool(std::size_t)> & f);
void deutsch_jozsa(Qcircuit & qc, std::function<bool(std::size_t)> f);
/*
* apply Grover rotation to qc's head_n q-bits from head.
* Grover rotation G is equal to (2|ψ><ψ| - I)O,
* whire O is quantum oracle and |ψ> = 1 / √(2^n) Σ |x>.
*/
void grover_rotation(Qcircuit & qc,
    qbitsize head_n,
    std::function<Qstate(Qstate &)> & qoracle);

/*
* Grover's search algorithm
* - O(√N) time where N = 2^n, N is total data size.
* - Pr(success) = Θ(1)
* - χ : {0,1,2,...,N-1} → Bool
*/
void grover_search(Qcircuit & qc,
    const std::function<bool(std::size_t)> & chi,
    std::size_t sol_n);

#endif
