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
  IntegratorSimpleStep(System* sys);
  virtual ~IntegratorSimpleStep();
  double SomeMethod ();
  void integrate(std::vector<Vector> *vec, System* system);
  static void dfdt (const Vector &x, Vector &res, const double /*t*/);
 private:

  System* sys;
};

template <typename Vector, typename System>
IntegratorSimpleStep<Vector, System>::IntegratorSimpleStep(System* sys) {
  this->sys = sys;
}
template <typename Vector, typename System>
IntegratorSimpleStep<Vector, System>::~IntegratorSimpleStep() {
  // TODO Auto-generated destructor stub
}
template <typename Vector, typename System>
double IntegratorSimpleStep<Vector, System>::SomeMethod (){
  std::cout << "I am working" << std::endl;
  return 2.0;
}

template <typename Vector, typename System>
void IntegratorSimpleStep<Vector, System>::integrate (std::vector<Vector> *vec, System* system){

  std::cout << "Inside Integrator" << std::endl;

  //integrate_const( stepper , dfdt , x , 0.0 , 10.0 , 0.01 );
  const double dt = 0.001;
//  std::cout << "t = " << 0 << ", " << x[0] << ", " << x[1] << ", " << x[2] << ", "  << x[3] << std::endl;
//  double e0 = sumE(x);
//  double e1;
  Vector x0;
  sys->getInitialCondition(x0);
  Vector res(4);
  sys->print();
  boost::numeric::odeint::runge_kutta4< Vector > stepper;

  static std::function<void(const Vector&, Vector&, const double)> F = [&](const Vector& x, Vector& res, const double t){
    system->dfdt(x, res, t);
  };
  for( double t=0.0 ; t<10 ; t+= dt ){
    stepper.do_step(F , x0 , t , dt);
    std::cout << x0[0] << std::endl;
  }
}
template <typename Vector, typename System>
void IntegratorSimpleStep<Vector, System>::dfdt (const Vector &x, Vector &res, const double /*t*/){
//  sys->dfdt(x,res,0);
  res[0] = 1;
  res[1] = 2;
  res[3] = 3;
  res[4] = 4;
}
//template <typename Vector, typename System>
//Vector IntegratorSimpleStep<Vector, System>::dfdt (){
//
//
//}

#endif /* INCLUDE_INTEGRATORSIMPLESTEP_HPP_ */
