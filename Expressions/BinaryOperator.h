
#ifndef EX3_NEW_BINARYOPERATOR_H
#define EX3_NEW_BINARYOPERATOR_H

#include "Expressions.h"
#include "../DataHandlers/DataManager.h"

/**
 * BinaryOperator class
 */
class BinaryOperator : public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    BinaryOperator(Expression* left, Expression* right);
    ~BinaryOperator() override;
};


#endif //EX3_NEW_BINARYOPERATOR_H
