
#ifndef EX3_NEW_PLUS_H
#define EX3_NEW_PLUS_H

#include "Expressions.h"
#include "BinaryOperator.h"

/**
 * Plus class
 */
class Plus : public BinaryOperator {
public:
    Plus(Expression* left, Expression* right);
    double calculate();
};


#endif //EX3_NEW_PLUS_H
