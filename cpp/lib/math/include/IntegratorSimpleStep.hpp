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

template<typename Vector, typename System>
class IntegratorSimpleStep : public Integrator<Vector, System> {

 public:
  IntegratorSimpleStep(System* sys, const double timestep);
  virtual ~IntegratorSimpleStep();
  double SomeMethod ();
  void integrate(std::vector<Vector> *vec);
  static void dfdt (const Vector &x, Vector &res, const double /*t*/);
 private:
  
	double timestep;
  System* sys;
  boost::numeric::odeint::runge_kutta4< Vector > stepper;
};

template <typename Vector, typename System>
IntegratorSimpleStep<Vector, System>::IntegratorSimpleStep(System* sys, const double timestep) {
  this->sys = sys;
	this->timestep = timestep;
}

template <typename Vector, typename System>
IntegratorSimpleStep<Vector, System>::~IntegratorSimpleStep() {
}

template <typename Vector, typename System>
double IntegratorSimpleStep<Vector, System>::SomeMethod (){
  std::cout << "I am working" << std::endl;
  return 2.0;
}

template <typename Vector, typename System>
void IntegratorSimpleStep<Vector, System>::integrate (std::vector<Vector> *vec){

  Vector x0;
  sys->getInitialCondition(x0);
  sys->print();
  double tMax = sys->getEndTime();
  auto F = [&](const Vector& x, Vector& res, const double t){
    sys->dfdt(x, res, t);
  };
	
  std::cout << "Integrating from 0 to " << tMax << " seconds.." << std::endl;

  for( double t=0.0 ; t<tMax ; t+= timestep){
	stepper.do_step(F , x0 , t , timestep);
	(*vec).push_back(x0);
  }
}

#endif /* INCLUDE_INTEGRATORSIMPLESTEP_HPP_ */
