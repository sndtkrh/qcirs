#ifndef INTERPRETER
#define INTERPRETER
namespace qcparser {
  const bool deterministic = true;
  const bool random = false;
  
  struct env{
    env();
    ~env();
    std::map<std::string, qc::Qcircuit *> qc;
    std::map<std::string, const qc::UnitaryMat *> um;
    bool interactive;

    bool measure_way; // deterministic or random
    bool measure_printpr;
  };

  struct run_command : boost::static_visitor<void> {
    run_command(env * e_);
    void operator()(define & c) const;
    void operator()(measure & c) const;
    void operator()(print & c) const;
    void operator()(add & c) const;
    env * e_;
  private:
    bool exist_qc(std::string & qc_indicator) const;
    bool exist_um(std::string & qc_indicator) const;
  };

  struct run_program : boost::static_visitor<void> {
    run_program(env * e_);
    void operator()(std::string & p) const; // comment
    void operator()(command & c) const;
    env * e_;
  };

  void interpret(program p, env & e);
}
#endif
