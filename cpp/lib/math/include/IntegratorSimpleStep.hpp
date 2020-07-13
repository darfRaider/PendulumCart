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
  
  typedef typename TMechanicalSystem::TState TState;
  typedef typename TMechanicalSystem::TInput TInput;
  typedef typename TMechanicalSystem::System TSystem; 
 
 public:
  IntegratorSimpleStep(const TSystem* sys, TState x0, const double timestep);
 
  virtual ~IntegratorSimpleStep();
  
  void integrate(const double t0,
	  const double t1, 
	  std::vector<TState> *vec,
	  std::vector<double>* tout = NULL);

  void integrate(const double t0,
	  const double t1, 
	  std::vector<TState> *vec,
	  std::vector<TInput> *input,
	  double Tsampling,
	  std::vector<double>* tout = NULL);
 
 private:
  double timestep;
  boost::numeric::odeint::runge_kutta4< TState > stepper;
};

template <typename TMechanicalSystem>
IntegratorSimpleStep<TMechanicalSystem>::
IntegratorSimpleStep(const TSystem* sys, TState x0, const double timestep) { 
  this->sys = sys;
  this->x0 = x0;
  this->timestep = timestep;
}

template <typename TMechanicalSystem>
IntegratorSimpleStep<TMechanicalSystem>::~IntegratorSimpleStep() {
}

template <typename TMechanicalSystem>
void IntegratorSimpleStep<TMechanicalSystem>::
integrate (const double t1, const double t2, std::vector<TState> *vec, std::vector<double>* tout) {
  TState x0 = this->x0;
  auto F = [&](const TState& x, TState& res, const double t){
    this->sys->dfdt(x, res, t);
  };
  (*vec).push_back(x0);
  if(tout != NULL)
   (*tout).push_back(0);	
  for(int i = 0; i < 4; i++){
	std::cout << x0[i] << ",";
  }
  std::cout << std::endl;
  for( double t=t1 ; t<t2 ; t+= timestep){
	stepper.do_step(F , x0 , t , timestep);
	(*vec).push_back(x0);
	if(tout != NULL)
	  (*tout).push_back(t+timestep);
  }
}

template <typename TMechanicalSystem>
void IntegratorSimpleStep<TMechanicalSystem>::
integrate(const double t1, const double t2, std::vector<TState> *vec,
	std::vector<TInput>* input, double Tsampling, std::vector<double>* tout) {
  this->setInputSequence(input, Tsampling);
  TState x0 = this->x0;
  (*vec).push_back(x0); 
  if(tout != NULL)
   (*tout).push_back(0);	

  auto F = [&](const TState& x, TState& res, const double t){
	TInput u;
	this->getInput(t,u);	
  	this->sys->dfdt(x, res, t, u);
  };
  
  for( double t=t1 ; t<t2 ; t+= timestep){
	stepper.do_step(F , x0 , t , timestep);
	(*vec).push_back(x0);
	if(tout != NULL)
	  (*tout).push_back(t+timestep);
  }
}
  
#endif /* INCLUDE_INTEGRATORSIMPLESTEP_HPP_ */
