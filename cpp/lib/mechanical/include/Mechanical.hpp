#ifndef MECHANICAL_HPP
#define MECHANICAL_HPP
#include "System.hpp"

template<typename TMechanicalModel>
class Mechanical {
 public:
  typedef typename TMechanicalModel::System TSystem; 
  typedef typename TMechanicalModel::System::TState TState;
  typedef typename TMechanicalModel::System::TInput TInput;
   Mechanical(TMechanicalModel* model);
   ~Mechanical();

 private:
   TSystem* sys;
};


template<typename MechanicalModel>
Mechanical<MechanicalModel>::Mechanical(MechanicalModel* model){
  this->sys = model; 
  TState x0, x1;
  x0 = {0,0,0,0};
}

template<typename MechanicalModel>
Mechanical<MechanicalModel>::~Mechanical() {}

#endif
