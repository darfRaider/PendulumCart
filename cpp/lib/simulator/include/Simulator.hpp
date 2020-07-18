#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP
#include <vector>
#include <iostream>
template<typename TMechanicalModel, typename TIntegrator>
class Simulator {

 public:
  typedef typename TMechanicalModel::TState TState;
  typedef typename TMechanicalModel::TInput TInput;
  typedef typename std::vector<TInput> TInputSequence;
   
  const static int UNASSIGNED = -1;
  
  struct config {
	double dT_integrator =		UNASSIGNED;
	double dT_inputSequence =	UNASSIGNED;
	double tSimulation =		UNASSIGNED;
	TState x0;
  };	
  
  Simulator(TMechanicalModel* sys, config& cfg);
  ~Simulator();
  void setInputSequence(TInputSequence* inputSequence, double Ts);
  static std::vector<double>* getStateVector(int stateNr, std::vector<TState>* res); 
  void simulate(std::vector<TState>* res, std::vector<double>* tout = NULL); 
private:
  
  config cfg;

  const TMechanicalModel* sys;
  TIntegrator* integrator = 0;
  TInputSequence* inputSequence = 0;
  double Ts_input;
  std::vector<TState>* result = NULL;
};

// Public functions implementation

template<typename TMechanicalModel, typename Integrator>
Simulator<TMechanicalModel, Integrator>::Simulator(TMechanicalModel* sys, config& cfg) : sys(sys), cfg(cfg) {
}

template<typename TMechanicalModel, typename Integrator>
Simulator<TMechanicalModel, Integrator>::~Simulator() {
}


template<typename TMechanicalModel, typename Integrator>
void Simulator<TMechanicalModel, Integrator>::setInputSequence(TInputSequence* inputSequence, double Ts){
  this->inputSequence = inputSequence;
  this->Ts_input = Ts;
}

// Private functions impelemntation

template<typename TMechanicalModel, typename Integrator>
void Simulator<TMechanicalModel, Integrator>::simulate(std::vector<TState>* res, std::vector<double>* tout){
  integrator = new Integrator(sys, cfg.x0, cfg.dT_integrator);
  if(tout == NULL)
	integrator->integrate(0, cfg.tSimulation, res);
  else
	integrator->integrate(0, cfg.tSimulation, res, tout);
  this->result = res; 
  delete integrator;  
}

template<typename TMechanicalModel, typename Integrator>
std::vector<double>* Simulator<TMechanicalModel, Integrator>::getStateVector(int stateNr, std::vector<TState>* res) {
  std::vector<double>* state = new std::vector<double>();
  if(res == NULL){
	return state;
  }
  for(int i = 0; i < (*res).size(); i++){
	(*state).push_back((*res)[i][stateNr]);
  }
  return state;
}
#endif
