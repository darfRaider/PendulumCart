/*
 * Physics.hpp
 *
 *  Created on: Jun 15, 2020
 *      Author: sam
 */

#ifndef INCLUDE_PHYSICS_HPP_
#define INCLUDE_PHYSICS_HPP_

#include <vector>
#include <math.h>

class Physics {
 public:
  Physics();
  virtual ~Physics();
 protected:
  /**
   * @brief Acceleration at earth surface \f$(\frac{m}{s^2})\f$
   */
  const static double GRAVITY;

  /**
   * @brief Gravitational constant \f$(\frac{m^3}{kg\cdot s^2})\f$
   */
  const static double G_CONSTANT;
};

#endif /* INCLUDE_PHYSICS_HPP_ */
