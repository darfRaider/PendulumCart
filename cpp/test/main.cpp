#include <gtest/gtest.h>
#include "IntegratorSimpleStep.hpp"
#include "Pendulum2d.hpp"
#include "Simulator.hpp"
#include "stdio.h"

TEST(ConsoleTest, coloredText){
  printf("\x1B[31mRed normal text\033[0m\n");
  printf("\x1B[1;92mBright green bold text\033[0m\n");
			  // bg,fg
  printf("\033[1;102;90mBright green background, black bold text\033[0m\n");
// https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
}

TEST(SimulatorTest, instanciating){
  typedef Pendulum2d TSelectedSystem;
  typedef IntegratorSimpleStep<TSelectedSystem> TIntegrator;

  typedef typename TSelectedSystem::TState TState;
  typedef typename TSelectedSystem::TInput TInput;
  typedef Simulator<TSelectedSystem, TIntegrator> TSimulator;
  typedef typename TSimulator::config TConfig; 
  
  Pendulum2d* p = new Pendulum2d(1000,2,3);  
  System<TState, TInput>* sys = p; 
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
