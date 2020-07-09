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
  
  void simulate(std::vector<TState>* res); 
private:
  
  config cfg;

  const TSystem* sys;
  TIntegrator* integrator = 0;
  TInputSequence* inputSequence = 0;
  double Ts_input;
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
void Simulator<TMechanicalModel, Integrator>::setInputSequence(TInputSequence* inputSequence, double Ts){
  this->inputSequence = inputSequence;
  this->Ts_input = Ts;
}

// Private functions impelemntation

template<typename TMechanicalModel, typename Integrator>
void Simulator<TMechanicalModel, Integrator>::simulate(std::vector<TState>* res){
  // Invalid cases, return
  if((inputSequence == 0 && cfg.tSimulation == UNASSIGNED) || 
	  cfg.dT_integrator == UNASSIGNED)
	return;


  // TODO: feed in dfdt in new Integrator 
  integrator = new Integrator(sys, cfg.x0, cfg.dT_integrator);
  auto F = [&](const TState& x, TState& res, const double t){
	sys->dfdt(x, res, t);
  };
  //integrator = new Integrator(cfg.x0, cfg.dT_integrator, &F);
  
  // No input sequence defined simulate form t=(0,tSimulation)
  if(inputSequence == 0){
	std::cout << "No input sequence selected" << std::endl;	
	integrator->integrate(cfg.tSimulation, res);
	return;
  }
  
  // No sim end time defined simulate from t=(0,inputSequence.size()*dT_inputSequence) 
  else if(cfg.tSimulation == UNASSIGNED){
	// TODO
	return; 
  }

  // Input sequence and simTime defined, simulate from t = (0, tSimulation)
  else {
	// TODO
  }

  delete integrator;  
}

#endif
