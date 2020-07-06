#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP
#include <vector>

template<typename System, typename TIntegrator>
class Simulator {

 public:
  typedef typename System::TState TState;
  typedef typename System::TInput TInput;
  typedef typename std::vector<TInput> TInputSequence;
  
  Simulator(System* sys);
  ~Simulator();
  void setInputSequence(TInputSequence* inputSequence, double Ts);

private:
  const System* sys;
  TIntegrator* integrator = 0;
  TInputSequence* inputSequence = 0;
  TState x0;
};


template<class System, class Integrator>
Simulator<System, Integrator>::Simulator(System* sys) : sys(sys) {
}

template<class System, class Integrator>
Simulator<System, Integrator>::~Simulator() {
  if(integrator != 0)
	delete integrator;
}



#endif
