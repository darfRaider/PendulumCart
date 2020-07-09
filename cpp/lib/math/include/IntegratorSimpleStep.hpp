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
template<typename TMechanicalSystem>
class IntegratorSimpleStep : public Integrator<TMechanicalSystem> {
  typedef typename TMechanicalSystem::TState Vector;
  typedef typename TMechanicalSystem::System TSystem; 
 
 public:
  IntegratorSimpleStep(const TSystem* sys, Vector x0, const double timestep);
  virtual ~IntegratorSimpleStep();
  void integrate(double tMax, std::vector<Vector> *vec);
  void integrate(const double t0, const double t1, std::vector<Vector> *vec);
 private:
  double timestep;
  boost::numeric::odeint::runge_kutta4< Vector > stepper;
};

template <typename TMechanicalSystem>
IntegratorSimpleStep<TMechanicalSystem>::
IntegratorSimpleStep(const TSystem* sys, Vector x0, const double timestep) { 
  this->sys = sys;
  this->x0 = x0;
  this->timestep = timestep;
}

template <typename TMechanicalSystem>
IntegratorSimpleStep<TMechanicalSystem>::~IntegratorSimpleStep() {
}

template <typename TMechanicalSystem>
void IntegratorSimpleStep<TMechanicalSystem>::integrate (const double t1, const double t2, std::vector<Vector> *vec){
  Vector x0 = this->x0;
  auto F = [&](const Vector& x, Vector& res, const double t){
    this->sys->dfdt(x, res, t);
  };
  for( double t=t1 ; t<t2 ; t+= timestep){
	stepper.do_step(F , x0 , t , timestep);
	(*vec).push_back(x0);
  }
}

template <typename TMechanicalSystem>
void IntegratorSimpleStep<TMechanicalSystem>::integrate (double tMax, std::vector<Vector> *vec){
  integrate(0, tMax, vec);
}

#endif /* INCLUDE_INTEGRATORSIMPLESTEP_HPP_ */
