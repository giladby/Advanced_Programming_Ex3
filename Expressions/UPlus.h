
#ifndef EX3_NEW_UPLUS_H
#define EX3_NEW_UPLUS_H

#include "Expressions.h"
#include "UnaryOperator.h"

/**
 * UPlus class
 */
class UPlus : public UnaryOperator {
public:
    UPlus(Expression* exp);
    double calculate();
};


#endif //EX3_NEW_UPLUS_H
