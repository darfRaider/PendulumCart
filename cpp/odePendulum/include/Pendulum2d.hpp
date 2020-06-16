/*
 * Pendulum2d.hpp
 *
 *  Created on: Jun 15, 2020
 *      Author: sam
 */

#ifndef INCLUDE_PENDULUM2D_HPP_
#define INCLUDE_PENDULUM2D_HPP_
#include "Physics.hpp"

class Pendulum2d : protected Physics {

 public:
  typedef std::vector<double> Vector;
  struct statePendulum2D {
    double x = 0;
    double dx = 0;
    double theta = 0;
    double dtheta = 0;
  };

  Pendulum2d(const double m, const double M, const double L);

  virtual ~Pendulum2d();

  void dfdt(const Vector &x, Vector &res, const double /*t*/) const;


  void print();

  void getInitialCondition(Vector &x0);
  void setInitialCondition(Vector &x0);

 private:
  double m, M, L;
  Vector initialCondition;
};

#endif /* INCLUDE_PENDULUM2D_HPP_ */
