
#include "Div.h"

// Div class methods

Div::Div(Expression *inputLeft, Expression *inputRight) : BinaryOperator(inputLeft, inputRight) {}

double Div::calculate() {
    //chec
    if(this->right->calculate() == 0) {
        cerr << "Cannot divide by 0"<<endl;
        exit(1);
    }
    return this->left->calculate() / this->right->calculate();
}
