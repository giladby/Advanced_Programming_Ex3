
#include "UPlus.h"

// UPlus class methods

UPlus::UPlus(Expression *inputExp) : UnaryOperator(inputExp) {}
double UPlus::calculate() {
    return this->exp->calculate();
}


