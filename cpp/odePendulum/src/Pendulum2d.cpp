/*
 * Pendulum2d.cpp
 *
 *  Created on: Jun 15, 2020
 *      Author: sam
 */

#include "Pendulum2d.hpp"
#include <iostream>
Pendulum2d::Pendulum2d(const double m, const double M, const double L):
  m(m),
  M(M),
  L(L)
{ }

Pendulum2d::~Pendulum2d() {
  // TODO Auto-generated destructor stub
}

void Pendulum2d::dfdt(const Vector &x, Vector &res, const double /*t*/) const {
  double u = 0;
  double M = this->M;
  double m = this->m;
  double L = this->L;
  res[0] = x[1];
  res[1] = ((M*GRAVITY*sin(2*x[2]))/2.0 + M*L*pow(x[3],2)*sin(x[2]) + u)/(M*pow(sin(x[2]),2) + m);
  res[2] = x[3];
  res[3] = -(M*GRAVITY*sin(x[2]) + M*L*pow(x[3],2)*sin(2*x[2])/2.0 +
             GRAVITY*m*sin(x[2]) + u*cos(x[2]))/(L*(M*pow(sin(x[2]),2) + m));
}


void Pendulum2d::getInitialCondition(Vector &x0){
  x0 = initialCondition;
}

void Pendulum2d::setInitialCondition(Vector &x0){
  initialCondition = x0;
}

void Pendulum2d::print(){
  std::cout << "m = " << m << ", M = " << M << ", L = " << L << std::endl;
}
