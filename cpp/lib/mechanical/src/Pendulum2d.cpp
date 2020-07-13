/*
 * Pendulum2d.cpp
 *
 *  Created on: Jun 15, 2020
 *      Author: sam
 */

#include "Pendulum2d.hpp"
#include <iostream>

const Pendulum2d::TInput Pendulum2d::zeroInput = 0;

Pendulum2d::Pendulum2d(const double m, const double M, const double L):
  m(m),
  M(M),
  L(L)
{ 
}

Pendulum2d::~Pendulum2d() { }

void Pendulum2d::dfdt(const TState &x, TState &res, const double t, const double u) const {
  res[0] = x[1];
  res[1] = ((M*GRAVITY*sin(2*x[2]))/2.0 + M*L*pow(x[3],2)*sin(x[2]) + u)/(M*pow(sin(x[2]),2) + m);
  res[2] = x[3];
  res[3] = -(M*GRAVITY*sin(x[2]) + M*L*pow(x[3],2)*sin(2*x[2])/2.0 +
             GRAVITY*m*sin(x[2]) + u*cos(x[2]))/(L*(M*pow(sin(x[2]),2) + m));
}

void Pendulum2d::getZeroInput(TInput& u) const {
  u = zeroInput;
}

void Pendulum2d::print() const {
  std::cout << "m = " << m << ", M = " << M << ", L = " << L << std::endl;
}

void Pendulum2d::printParameters() const {

}

double Pendulum2d::sumE(const TState x) const {
  return ePot(x)+eKin(x);
}

double Pendulum2d::ePot(const TState x) const {
  return (1-cos(x[2]))*L*M*GRAVITY;
}

double Pendulum2d::eKin(const TState x) const {
  double eC = 0.5*m*x[1]*x[1];
  double vMx = x[1]+x[3]*L*cos(x[2]);
  double vMy = x[3]*L*sin(x[2]);
  double eM = 0.5*M*(vMx*vMx+vMy*vMy);
  return eC+eM;
}

double Pendulum2d::getTotalMass() const {
 return m+M; 
}

/*
Pendulum2d::TInput Pendulum2d::getInput(const double t) const {
  int k = (int) t/Ts;
  return inputSequence[k];
}
*/
