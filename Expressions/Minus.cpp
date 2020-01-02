
#include "Minus.h"

// Minus class methods

Minus::Minus(Expression *inputLeft, Expression *inputRight) : BinaryOperator(inputLeft, inputRight) {}

double Minus::calculate() {
    return this->left->calculate() - this->right->calculate();
}
