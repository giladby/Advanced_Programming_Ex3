
#ifndef EX3_NEW_UMINUS_H
#define EX3_NEW_UMINUS_H

#include "Expressions.h"
#include "UnaryOperator.h"

/**
 * UMinus class
 */
class UMinus : public UnaryOperator {
public:
    UMinus(Expression* exp);
    double calculate();
};



#endif //EX3_NEW_UMINUS_H
