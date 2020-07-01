/*
 * Pendulum2d.cpp
 *
 *  Created on: Jun 15, 2020
 *      Author: sam
 */

#include "Pendulum2d.hpp"
#include <iostream>

Pendulum2d::Pendulum2d(const double m, const double M, const double L, const double Ts):
  m(m),
  M(M),
  L(L),
  Ts(Ts)
{ }

Pendulum2d::~Pendulum2d() { }

void Pendulum2d::dfdt(const TState &x, TState &res, const double t){
  double u = 0;
  res[0] = x[1];
  res[1] = ((M*GRAVITY*sin(2*x[2]))/2.0 + M*L*pow(x[3],2)*sin(x[2]) + u)/(M*pow(sin(x[2]),2) + m);
  res[2] = x[3];
  res[3] = -(M*GRAVITY*sin(x[2]) + M*L*pow(x[3],2)*sin(2*x[2])/2.0 +
             GRAVITY*m*sin(x[2]) + u*cos(x[2]))/(L*(M*pow(sin(x[2]),2) + m));
}


void Pendulum2d::getInitialCondition(TState &x0){
  x0 = initialCondition;
}

void Pendulum2d::setInitialCondition(TState &x0){
  initialCondition = x0;
}

void Pendulum2d::setInputSequence(std::vector<TInput>* seq){
  this->inputSequence = *seq;
}

double Pendulum2d::getEndTime(){
  return inputSequence.size()*Ts;
}

void Pendulum2d::print(){
  std::cout << "m = " << m << ", M = " << M << ", L = " << L << std::endl;
}

double Pendulum2d::sumE(TState x){
  return ePot(x)+eKin(x);
}

double Pendulum2d::ePot(TState x){
  return (1-cos(x[2]))*L*M*GRAVITY;
}

double Pendulum2d::eKin(TState x){
  double eC = 0.5*m*x[1]*x[1];
  double vMx = x[1]+x[3]*L*cos(x[2]);
  double vMy = x[3]*L*sin(x[2]);
  double eM = 0.5*M*(vMx*vMx+vMy*vMy);
  return eC+eM;
}

Pendulum2d::TInput Pendulum2d::getInput(double t){
  int k = (int) t/Ts;
  return inputSequence[k];
}
