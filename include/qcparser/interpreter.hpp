#ifndef INTERPRETER
#define INTERPRETER
namespace qcparser {
  struct env{
    env();
    ~env();
    std::map<std::string, Qcircuit *> qc;
    std::map<std::string, const UnitaryMat *> um;
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
