#ifndef INTERPRETER
#define INTERPRETER
namespace qcparser {
  struct env{
    std::map<std::string, Qcircuit *> qc;
    ~env();
  };

  struct run_command : boost::static_visitor<void> {
    run_command(env * e_);
    void operator()(qcparser::define & c) const;
    void operator()(qcparser::measure & c) const;
    void operator()(qcparser::print & c) const;
    env * e_;
  private:
    bool exist(std::string & qc_indicator) const;
  };

  struct run_program : boost::static_visitor<void> {
    run_program(env * e_);
    void operator()(std::string & p) const; // comment
    void operator()(qcparser::command & c) const;
    env * e_;
  };

  void interpret(program p, env & e);
}
#endif
