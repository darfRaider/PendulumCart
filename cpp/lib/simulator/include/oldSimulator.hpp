#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP
#include <vector>
#include <iostream>
template<typename System, typename TIntegrator>
class Simulator {

 public:
  typedef typename System::TState TState;
  typedef typename System::TInput TInput;
  typedef typename std::vector<TInput> TInputSequence;
   
  const static int UNASSIGNED = -1;
  
  struct config {
	double dT_integrator =		UNASSIGNED;
	double dT_inputSequence =	UNASSIGNED;
	double tSimulation =		UNASSIGNED;
	TState x0;
  };	
  
  Simulator(System* sys, config& cfg);
  ~Simulator();
  void setInputSequence(TInputSequence* inputSequence, double Ts);
  
  void simulate(std::vector<TState>* res); 
private:
  
  config cfg;

  const System* sys;
  TIntegrator* integrator = 0;
  TInputSequence* inputSequence = 0;
  double Ts_input;
};

// Public functions implementation

template<typename System, typename Integrator>
Simulator<System, Integrator>::Simulator(System* sys, config& cfg) : sys(sys), cfg(cfg) {
  std::vector<TState>* res = new std::vector<TState>();  
  simulate(res);   
}

template<typename System, typename Integrator>
Simulator<System, Integrator>::~Simulator() {
  if(integrator != 0)
	delete integrator;
}

template<typename System, typename Integrator>
void Simulator<System, Integrator>::setInputSequence(TInputSequence* inputSequence, double Ts){
  this->inputSequence = inputSequence;
  this->Ts_input = Ts;
}

// Private functions impelemntation

template<class System, typename Integrator>
void Simulator<System, Integrator>::simulate(std::vector<TState>* res){
  // Invalid cases, return
  if((inputSequence == 0 && cfg.tSimulation == UNASSIGNED) || 
	  cfg.dT_integrator == UNASSIGNED)
	return;


  // TODO: feed in dfdt in new Integrator 
  integrator = new Integrator(cfg.x0, cfg.dT_integrator);
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
