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
  const double GRAVITY = 9.81;
};

#endif /* INCLUDE_PHYSICS_HPP_ */
