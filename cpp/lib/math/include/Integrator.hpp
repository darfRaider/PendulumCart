/*
 * Integrator.hpp
 *
 *  Created on: Jun 15, 2020
 *      Author: sam
 */

#ifndef INCLUDE_INTEGRATOR_HPP_
#define INCLUDE_INTEGRATOR_HPP_
#include <iostream>
#include <boost/numeric/odeint.hpp>

template<typename TMechanicalModel>
class Integrator {
  public:
  typedef typename TMechanicalModel::TState TState;
  typedef typename TMechanicalModel::TInput TInput;
  typedef typename TMechanicalModel::TSystem TSystem; 
  virtual void integrate(double tMax, std::vector<TState> *vec) = 0;
  void setInitialCondition(TState x0); 
  TState x0; 
  const TSystem* sys;
};

template<typename TMechanicalModel>
void Integrator<TMechanicalModel>::setInitialCondition(TState x0){
  this->x0 = x0;
}

#endif /* INCLUDE_INTEGRATOR_HPP_ */
