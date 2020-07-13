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
typedef std::vector<double> StateType;
typedef double InputType;

typedef System<StateType,InputType> SystemType;

class Pendulum2d : protected Physics, public SystemType {

 public:
  typedef SystemType TSystem;
  Pendulum2d(const double m, const double M, const double L);
  virtual ~Pendulum2d();

  void dfdt(const TState &x, TState &res, const double t = 0, const double u = 0) const;
  void getZeroInput(TInput& u) const;
  
  void print() const;
  void printParameters() const;

  double sumE(const TState x) const;
  double ePot(const TState x) const;
  double eKin(const TState x) const;
  double getTotalMass() const;
  
  const static TInput zeroInput;

  private:
  double m, M, L;
};

#endif /* INCLUDE_PENDULUM2D_HPP_ */
