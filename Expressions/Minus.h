
#ifndef EX3_NEW_MINUS_H
#define EX3_NEW_MINUS_H

#include "Expressions.h"
#include "BinaryOperator.h"

/**
 * Minus class
 */
class Minus : public BinaryOperator {
public:
    Minus(Expression* left, Expression* right);
    double calculate();
};


#endif //EX3_NEW_MINUS_H
