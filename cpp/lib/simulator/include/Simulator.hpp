#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP
#include <vector>

template<typename System, typename TIntegrator>
class Simulator {

 public:
   Simulator(System* sys);
   ~Simulator();
  typedef typename System::TState TState;
  typedef typename System::TInput TInput;
 private:
  const System* sys;
  TIntegrator* integrator;
  std::vector<TInput>* inputSequence;
  TState x0;
};


template<class System, class Integrator>
Simulator<System, Integrator>::Simulator(System* sys) : sys(sys) {
}

template<class System, class Integrator>
Simulator<System, Integrator>::~Simulator() {}


#endif
