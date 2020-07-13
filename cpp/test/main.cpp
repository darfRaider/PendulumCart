#include <gtest/gtest.h>
#include "IntegratorSimpleStep.hpp"
#include "Pendulum2d.hpp"
#include "Simulator.hpp"



TEST(SimulatorTest, instanciating){
  typedef Pendulum2d TSelectedSystem;
  typedef IntegratorSimpleStep<TSelectedSystem> TIntegrator;

  typedef typename TSelectedSystem::TState TState;
  typedef typename TSelectedSystem::TInput TInput;
  typedef Simulator<TSelectedSystem, TIntegrator> TSimulator;
  typedef typename TSimulator::config TConfig; 
  
  Pendulum2d* p = new Pendulum2d(1000,2,3);  
  TConfig cfg;  
  TState res;
  TState x0 = {0,0,0.25,0};
  std::vector<TState>* resvec = new std::vector<TState>;
  cfg.dT_integrator = 0.001;
  cfg.tSimulation = 10; 
  cfg.x0 = x0; 

  TSimulator *s = new TSimulator(p, cfg); 
  s->simulate(resvec);
}

TEST(System, SystemAndPendulumMass){
  System<std::vector<double>,double>* s = new Pendulum2d(1,2,3);  
  EXPECT_EQ(3,s->getTotalMass()); 
}

int main(int argc, char* argv[]){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



  /*
TEST(IntegratorSimpleStep, zeroInput){
  std::vector<Pendulum2d::TInput> input;
  for(int i = 0; i < 100; i++){
	input.push_back(0);
  }
  Pendulum2d* p = new Pendulum2d(1,2,3,0.05);
//  p->setInputSequence(&input);
  Pendulum2d::TState x0 = {0,0,0,0};
  p->setInitialCondition(x0);
  std::vector<Pendulum2d::TState>* res = new std::vector<Pendulum2d::TState>;
  Integrator<Pendulum2d::TState>* integrator = 
	new IntegratorSimpleStep<Pendulum2d::TState>(x0,0.00132535);
  integrator->integrate(res);
 
  int nMax = res->size(); 
  for(int i = 0; i < 4; i++){
	EXPECT_EQ((*res)[nMax-1][i],0);
  }
}
*/
