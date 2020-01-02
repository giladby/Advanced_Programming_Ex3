
#include "Mul.h"

// Mul class methods

Mul::Mul(Expression *inputLeft, Expression *inputRight) : BinaryOperator(inputLeft, inputRight) {}

double Mul::calculate() {
    return this->left->calculate() * this->right->calculate();
}
