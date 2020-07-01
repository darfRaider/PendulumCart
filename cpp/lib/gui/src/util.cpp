#include "util.hpp"



// Test if value is > 0
bool isValidEntry(QLineEdit* ln){
    if(ln->text().toDouble() > 0){
        ln->setStyleSheet("background: white");
    }
    else{
        ln->setStyleSheet("background: red");
        return false;
    }
    return true;
}

// Test if values are valid
bool valuesAreValid(const bool* list){
    for(int i = 0; i < N_TEST_FIELDS; i++){
        if(!list[i])
            return false;
    }
    return true;
}
