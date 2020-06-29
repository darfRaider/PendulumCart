#include "util.hpp"
#include "QLineEdit"


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
