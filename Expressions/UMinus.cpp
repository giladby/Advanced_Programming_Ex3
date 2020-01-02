
#include "UMinus.h"

// UMinus class methods

UMinus::UMinus(Expression *inputExp) : UnaryOperator(inputExp) {}
double UMinus::calculate() {
    //avoid '-0' problem
    if(this->exp->calculate() == 0) {
        return this->exp->calculate();
    }
    return this->exp->calculate() * (-1);
}