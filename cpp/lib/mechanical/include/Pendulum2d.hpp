/*
 * Pendulum2d.hpp
 *
 *  Created on: Jun 15, 2020
 *      Author: sam
 */

#ifndef INCLUDE_PENDULUM2D_HPP_
#define INCLUDE_PENDULUM2D_HPP_
#include "Physics.hpp"

class Pendulum2d : protected Physics {

 public:
  typedef std::vector<double> TState;
	typedef double TInput;
  
	Pendulum2d(const double m, const double M, const double L, const double Ts);

  virtual ~Pendulum2d();

  void dfdt(const TState &x, TState &res, const double t);

  void print();

  void getInitialCondition(TState &x0);
  void setInitialCondition(TState &x0);
  void setInputSequence(std::vector<TInput>* seq);
  double getEndTime();

  double sumE(TState x);
  double ePot(TState x);
  double eKin(TState x);
 
	private:
	double m, M, L;
  double Ts; // Sampling time of of input (zero-order-hold)
	TState initialCondition;
  std::vector<TInput> inputSequence; 
	TInput getInput(double t);
};

#endif /* INCLUDE_PENDULUM2D_HPP_ */
