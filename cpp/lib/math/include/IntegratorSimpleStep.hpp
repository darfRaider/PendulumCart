/*
 * IntegratorSimpleStep.hpp
 *
 *  Created on: Jun 15, 2020
 *      Author: sam
 */

#ifndef INCLUDE_INTEGRATORSIMPLESTEP_HPP_
#define INCLUDE_INTEGRATORSIMPLESTEP_HPP_
#include "Integrator.hpp"
#include <functional>
#include <iostream>
template<typename Vector>
class IntegratorSimpleStep : public Integrator<Vector> {

 public:
  IntegratorSimpleStep(Vector x0, const double timestep);
  IntegratorSimpleStep(Vector x0, const double timestep, void (*pFun)(const Vector&, Vector, const double, const double));
  virtual ~IntegratorSimpleStep();
  void integrate(double tMax, std::vector<Vector> *vec);
  static void dfdt (const Vector &x, Vector &res, const double /*t*/);

 private:
  void (*pFun)(const Vector&, Vector, const double);
  Vector x0; 
  double timestep;
  boost::numeric::odeint::runge_kutta4< Vector > stepper;
};

template <typename Vector>
IntegratorSimpleStep<Vector>::IntegratorSimpleStep(Vector x0, const double timestep, void (*pFun)(const Vector&, Vector, const double, const double)) {
  this->pFun = pFun;
  this->timestep = timestep;
  this->x0 = x0;

}

template <typename Vector>
IntegratorSimpleStep<Vector>::IntegratorSimpleStep(Vector x0, const double timestep) {
  this->timestep = timestep;
  this->x0 = x0;
}

template <typename Vector>
IntegratorSimpleStep<Vector>::~IntegratorSimpleStep() {
}

template <typename Vector>
void IntegratorSimpleStep<Vector>::integrate (double tMax, std::vector<Vector> *vec){
  std::cout << "Inside integrator" << std::endl;
  Vector x0;
  /*auto F = [&](const Vector& x, Vector& res, const double t){
  //sys->dfdt(x, res, t);
  //};
  for( double t=0.0 ; t<tMax ; t+= timestep){
	stepper.do_step(F , x0 , t , timestep);
	(*vec).push_back(x0);
  }*/
}

#endif /* INCLUDE_INTEGRATORSIMPLESTEP_HPP_ */
