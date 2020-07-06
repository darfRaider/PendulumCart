#ifndef SYSTEM_HPP
#define SYSTEM_HPP

template <typename StateType, typename InputType>
class System {
 public:
  typedef StateType TState;
  typedef InputType TInput;
  struct systemParameters;
  
  // Compute derivative of nonlinear system 
  virtual void dfdt(const TState &x, TState &res, const double t, const double u = 0) = 0;
  
  // Compute energies  
  virtual double sumE(const TState x) const = 0;
  virtual double ePot(const TState x) const = 0;
  virtual double eKin(const TState x) const = 0;
  
  virtual double getTotalMass() const = 0;
  
  virtual void printParameters() const = 0;
  virtual void print() const = 0;
};

#endif
