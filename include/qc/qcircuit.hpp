#ifndef QCIRCUIT
#define QCIRCUIT
#include "common.hpp"
#include "bitoperation.hpp"
#include "matrices.hpp"
typedef std::vector<comp> Qstate;

class Qcircuit {
public:
  Qcircuit( qbitsize qbit_n );
  ~Qcircuit();
  void add_qgate_u(const UnitaryMat * U, const std::vector<qbitsize> & operand );
  void add_qgate_qmux(const std::vector<const UnitaryMat *> & Us,
      const std::vector<qbitsize> & controller,
      const std::vector<qbitsize> & operand);
  // f : {0,1}^(controller.size()) -> {0,1} |-> Uf : unitary transformation
  void add_qgate_qmux(const std::function<bool(std::size_t)> & f,
      const std::vector<qbitsize> & controller,
      qbitsize operand);

  void pop_back_qgate();

  /*
  * customized quamtum gate
  * Note that this method does not ensure that f is an unitary transformation.
  * You have to prove it.
  */
  void add_qgate_custom(const std::function<Qstate(Qstate &)> & f);

  qbitsize get_qbit_n() const;
  const Qstate & get_state() const;
  void set_state(const Qstate & s);
  comp & state_at(std::size_t q_idx);
  void run();
  std::vector<double> measure(std::vector<qbitsize> computational_basis);
  Qstate get_most_likely_state_after_measurement(
      std::vector<qbitsize> computational_basis );

private:
  qbitsize qbit_n;
  Qstate state;
  class Qgate{
  public:
    virtual ~Qgate();
    void set_qc(Qcircuit * qc_);
    Qcircuit & get_qc() const;
    virtual void act() = 0;
  private:
    Qcircuit * qc;
  };

  std::vector<Qgate * > qgate;

  class QgateU : public Qgate {
  public:
    QgateU();
    QgateU( Qcircuit * qc, const UnitaryMat * U, const std::vector<qbitsize> & operand );
    void act();
  private:
    const UnitaryMat * U;
    std::vector<qbitsize> operand;
  };
  class QgateQMUX : public Qgate { // quantum multiplexer
  public:
    QgateQMUX();
    QgateQMUX( Qcircuit * qc,
              const std::vector<const UnitaryMat *> & Us,
              const std::vector<qbitsize> & controller,
              const std::vector<qbitsize> & operand);
    void act();
  private:
    std::vector<const UnitaryMat *> Us;
    std::vector<qbitsize> controller;
    std::vector<qbitsize> operand;
  };
  class QgateCustom : public Qgate {
  public:
    QgateCustom();
    QgateCustom( Qcircuit * qc, const std::function<Qstate(Qstate &)> & f );
    void act();
  private:
    std::function<Qstate(Qstate &)> f;
  };
};

std::string state_to_string(Vec a, qbitsize qbit_n);
bool no_duplication( const std::vector<qbitsize> & v );

#endif
