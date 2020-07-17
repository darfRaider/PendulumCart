#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <string>

template <typename StateType, typename InputType>
class System {
 public:
   /**
	* @brief Datatype used for state representation.
	*/
  typedef StateType TState;

  /**
   * @brief Datatype used for input representation.
   */
  typedef InputType TInput;
  struct systemParameters;
  
  // Compute derivative of nonlinear system 
  virtual void dfdt(const TState &x, TState &res, const double t, const double u = 0) const = 0;
  
  // Compute energies  
  virtual double sumE(const TState x) const = 0;
  virtual double ePot(const TState x) const = 0;
  virtual double eKin(const TState x) const = 0;
  
  virtual double getTotalMass() const = 0;
  virtual void getZeroInput(TInput& u) const = 0;
  
  virtual std::string getStateUnit(const int i) const = 0;
  virtual void print() const = 0;

  virtual int getNstates() const = 0;
  virtual int getNinputs() const = 0;
};

#endif
