#include <gtest/gtest.h>
#include "IntegratorSimpleStep.hpp"

TEST(MyFirstTest, LOL){
  EXPECT_EQ(0, 0);
}

TEST(Integrator, checkZeroIntegration){
  EXPECT_EQ(0, 1);
}


int main(int argc, char* argv[]){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
