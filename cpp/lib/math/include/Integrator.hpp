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

template<typename Vector>
class Integrator {
  public:
  virtual void integrate(double tMax, std::vector<Vector> *vec) = 0;
};

#endif /* INCLUDE_INTEGRATOR_HPP_ */
