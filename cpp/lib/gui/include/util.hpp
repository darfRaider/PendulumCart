#ifndef UTIL_HPP
#define UTIL_HPP
#include <iostream>
#include "QLineEdit"

// Following definitions to keep track of input fields
static const int N_TEST_FIELDS = 6;
#define IDX_MASS_PENDULUM   0
#define IDX_MASS_CART       1
#define IDX_LENGTH          2
#define IDX_SIM_TIME        3
#define IDX_SIM_TIMESTEP    4
#define IDX_INT_TIMESTEP    5

// Test if Line value is valid
bool isValidEntry(QLineEdit* ln);
#endif
