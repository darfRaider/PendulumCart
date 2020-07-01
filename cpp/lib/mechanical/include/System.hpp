template <typename type_state, typename type_input>
class System {
 public:
  typedef type_state TState;
  typedef type_input TInput;
  struct systemParameters;
  
  virtual void dfdt(const TState &x, TState &res, const double t) = 0;
  
  virtual double sumE(const TState x) const = 0;
  virtual double ePot(const TState x) const = 0;
  virtual double eKin(const TState x) const = 0;
  
  virtual double getTotalMass() const = 0;
  virtual void print() = 0;


 private:
  int nX;
  int nY;
  double Ts;
};
