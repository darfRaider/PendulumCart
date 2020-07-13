#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP
#include <vector>
#include <iostream>
template<typename TMechanicalModel, typename TIntegrator>
class Simulator {

 public:
  typedef typename TMechanicalModel::System TSystem;
  typedef typename TSystem::TState TState;
  typedef typename TSystem::TInput TInput;
  typedef typename std::vector<TInput> TInputSequence;
   
  const static int UNASSIGNED = -1;
  
  struct config {
	double dT_integrator =		UNASSIGNED;
	double dT_inputSequence =	UNASSIGNED;
	double tSimulation =		UNASSIGNED;
	TState x0;
  };	
  
  Simulator(TSystem* sys, config& cfg);
  ~Simulator();
  void setInputSequence(TInputSequence* inputSequence, double Ts);
  std::vector<double>* getStateVector(int stateNr); 
  void simulate(std::vector<TState>* res, std::vector<double>* tout = NULL); 
private:
  
  config cfg;

  const TSystem* sys;
  TIntegrator* integrator = 0;
  TInputSequence* inputSequence = 0;
  double Ts_input;
  std::vector<TState>* result = NULL;
};

// Public functions implementation

template<typename TMechanicalModel, typename Integrator>
Simulator<TMechanicalModel, Integrator>::Simulator(TSystem* sys, config& cfg) : sys(sys), cfg(cfg) {
}

template<typename TMechanicalModel, typename Integrator>
Simulator<TMechanicalModel, Integrator>::~Simulator() {
  if(integrator != 0)
	delete integrator;
}

template<typename TMechanicalModel, typename Integrator>
std::vector<double>* Simulator<TMechanicalModel, Integrator>::getStateVector(int stateNr) {
  std::vector<double>* state = new std::vector<double>();
  if(result == NULL){
	return state;
  }
  for(int i = 0; i < (*result).size(); i++){
	(*state).push_back((*result)[i][stateNr]);
  }
  return state;
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

#endif
