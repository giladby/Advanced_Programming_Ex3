
#include "Div.h"

// Div class methods

Div::Div(Expression *inputLeft, Expression *inputRight) : BinaryOperator(inputLeft, inputRight) {}

double Div::calculate() {
    if(this->right->calculate() == 0) {
        throw "bad input";
    }
    return this->left->calculate() / this->right->calculate();
}
