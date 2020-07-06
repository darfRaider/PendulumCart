template <typename type_state, typename type_input>
class System {
 public:
  typedef type_state TState;
  typedef type_input TInput;
  struct systemParameters;
  
  // Compute derivative of nonlinear system 
  virtual void dfdt(const TState &x, TState &res, const double t, const double u = 0) = 0;
  
  // Compute energies  
  virtual double sumE(const TState x) const = 0;
  virtual double ePot(const TState x) const = 0;
  virtual double eKin(const TState x) const = 0;
  
  virtual double getTotalMass() const = 0;
  
  virtual void getInitialCondition(TState& x0) = 0;
  
//  virtual double getEndTime() const = 0;
  
  virtual void printParameters() const = 0;
  virtual void print() const = 0;
};
