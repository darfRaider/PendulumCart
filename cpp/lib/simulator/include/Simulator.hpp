#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

template<class System, class Integrator>
class Simulator {

 public:
   Simulator();
   ~Simulator();
  typedef typename System::TState TState;
  typedef typename System::TInput TInput;
 private:
  System* sys;
  Integrator* integrator;
};


template<class System, class Integrator>
Simulator<System, Integrator>::Simulator() {}



template<class System, class Integrator>
Simulator<System, Integrator>::~Simulator() {}
#endif
