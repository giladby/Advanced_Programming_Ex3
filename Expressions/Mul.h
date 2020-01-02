
#ifndef EX3_NEW_MUL_H
#define EX3_NEW_MUL_H

#include "Expressions.h"
#include "BinaryOperator.h"

/**
 * Multiply class
 */
class Mul : public BinaryOperator {
public:
    Mul(Expression* left, Expression* right);
    double calculate();
};


#endif //EX3_NEW_MUL_H
