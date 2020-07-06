#include <gtest/gtest.h>
#include "IntegratorSimpleStep.hpp"
#include "Pendulum2d.hpp"

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
  Integrator<Pendulum2d::TState, Pendulum2d>* integrator = 
	new IntegratorSimpleStep<Pendulum2d::TState,Pendulum2d>(p,0.00132535);
  integrator->integrate(res);
 
  int nMax = res->size(); 
  for(int i = 0; i < 4; i++){
	EXPECT_EQ((*res)[nMax-1][i],0);
  }
}

TEST(System, SystemAndPendulumMass){
  System<std::vector<double>,double>* s = new Pendulum2d(1,2,3,4);  
  EXPECT_EQ(3,s->getTotalMass()); 
}

int main(int argc, char* argv[]){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
