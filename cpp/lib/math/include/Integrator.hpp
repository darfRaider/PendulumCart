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
/**
 * @brief Interface for integrator implementation
 *
 * @tparam TMechanicalModel Type of mechanical system.
 */
template<typename TMechanicalModel>
class Integrator {
  typedef typename TMechanicalModel::TState TState;
  typedef typename TMechanicalModel::TInput TInput;

  public:
  /**
   * @brief Integration without input.
   *
   * @param t1 lower integration bound
   * @param t2 upper integration bound
   * @param vec pointer to vector that stores results
   */
  virtual void integrate(const double t1, 
						 const double t2, 
						 std::vector<TState> *vec,
						 std::vector<double>* tout = NULL) = 0;

  virtual void integrate(const double t1, 
						 const double t2, 
						 std::vector<TState> *vec,
						 std::vector<TInput> *input,
						 double Tsampling,
						 std::vector<double>* tout = NULL) = 0;

  void setInitialCondition(TState x0); 
  
  void setInputSequence(std::vector<TInput>* input, double Tsampling);
  void getInput(double t, TInput& input);
  bool hasInputSequence(); 

  TState x0; 
  const TMechanicalModel* sys;
  const static int UNASSIGNED = -1;
  
  private:
  int N_inputs = UNASSIGNED; 
  double Tsampling = UNASSIGNED;
  std::vector<TInput>* input = NULL;
};

template<typename TMechanicalModel>
void Integrator<TMechanicalModel>::setInputSequence(std::vector<TInput>* input, double Tsampling){
 this->input = input;
 this->Tsampling = Tsampling; 
 this->N_inputs = (*input).size();
}

template<typename TMechanicalModel>
void Integrator<TMechanicalModel>::getInput(double t, TInput& u){
  int index = t/Tsampling;
  if(index >= this->N_inputs){
	this->sys->getZeroInput(u);	
	return;	
  }
  u = (*input)[index];
}

template<typename TMechanicalModel>
void Integrator<TMechanicalModel>::setInitialCondition(TState x0){
  this->x0 = x0;
}

#endif /* INCLUDE_INTEGRATOR_HPP_ */
