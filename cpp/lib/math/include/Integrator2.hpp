/*
 * Integrator.hpp
 *
 *  Created on: Jun 15, 2020
 *      Author: sam
 */

#ifndef INCLUDE_INTEGRATOR2_HPP_
#define INCLUDE_INTEGRATOR2_HPP_
#include <iostream>
#include <boost/numeric/odeint.hpp>

template<typename TSystem>
class Integrator2 {
  
  public:
	typedef typename TSystem::TState Vector; 
	virtual void integrate(double tMax, std::vector<Vector> *vec) = 0;
};

#endif /* INCLUDE_INTEGRATOR_HPP_ */
