#include "util.hpp"
#include "QLineEdit"
void test(){
  std::cout << "test worked" << std::endl;
}

// Test if value is > 0
bool isValidEntry(QLineEdit* ln){
    //ln->
    std::cout << QPalette::Button << std::endl;
    if(ln->text().toDouble() > 0){
        ln->setStyleSheet("background: white");
    }
    else{
        ln->setStyleSheet("background: red");
    }
    return true;
}
