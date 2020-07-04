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

// Define State and Input representation
typedef std::vector<double> State;
typedef double Input;

class Pendulum2d : protected Physics, public System<State,Input> {

 public:
 Pendulum2d(const double m, const double M, const double L, const double Ts);
  virtual ~Pendulum2d();

  void dfdt(const TState &x, TState &res, const double t);

  void print() const;
  void printParameters() const;

  void getInitialCondition(TState &x0);
  void setInitialCondition(TState &x0);
  void setInputSequence(std::vector<TInput>* seq);
  double getEndTime() const;

  double sumE(const TState x) const;
  double ePot(const TState x) const;
  double eKin(const TState x) const;
  double getTotalMass() const;

  private:
  double m, M, L;
  double Ts; // Sampling time of of input (zero-order-hold)
  TState initialCondition;
  std::vector<TInput> inputSequence; 
  TInput getInput(const double t) const;
};

#endif /* INCLUDE_PENDULUM2D_HPP_ */
