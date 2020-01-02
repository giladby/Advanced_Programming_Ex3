
#ifndef EX3_NEW_DIV_H
#define EX3_NEW_DIV_H

#include "Expressions.h"
#include "BinaryOperator.h"

/**
 * Division class
 */
class Div : public BinaryOperator {
public:
    Div(Expression* left, Expression* right);
    double calculate();
};

#endif //EX3_NEW_DIV_H
