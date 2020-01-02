
#include "Plus.h"

// Plus class methods

Plus::Plus(Expression *inputLeft, Expression *inputRight) : BinaryOperator(inputLeft, inputRight) {}

double Plus::calculate() {
    return this->left->calculate() + this->right->calculate();
}