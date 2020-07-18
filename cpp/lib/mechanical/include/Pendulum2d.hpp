/*
 * Pendulum2d.hpp
 *
 *  Created on: Jun 15, 2020
 *      Author: sam
 */

#ifndef INCLUDE_PENDULUM2D_HPP_
#define INCLUDE_PENDULUM2D_HPP_

#include "Physics.hpp"
#include "System.hpp"

/**
 * @brief Datatype used for state representation.
 * 
 * Bla bla bla some more stuff.
 */
typedef std::vector<double> StateType;


/**
 * @brief Datatype used for input representation.
 *
 * The input is a force in \f$(N)\f$ acting on the cart in horizontal direction.
 */
typedef double InputType;

class Pendulum2d : protected Physics, public System<StateType, InputType> {

 public:
  const static int Nstates = 4;
  const static int Ninputs = 1;
  
  Pendulum2d(const double m, const double M, const double L);
  virtual ~Pendulum2d();

  void dfdt(const TState &x, TState &res, const double t = 0, const double u = 0) const;
  void getZeroInput(TInput& u) const;
  
  void print() const;
  void printParameters() const;
  static std::string getStateUnit(const int i);

  double sumE(const TState x) const;
  double ePot(const TState x) const;
  double eKin(const TState x) const;
  double getTotalMass() const;
  
  const static TInput zeroInput;
   
  int getNstates() const;
  int getNinputs() const; 

  private:
  double m, M, L;
};

#endif /* INCLUDE_PENDULUM2D_HPP_ */
