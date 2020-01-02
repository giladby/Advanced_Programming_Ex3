
#ifndef EX3_NEW_UNARYOPERATOR_H
#define EX3_NEW_UNARYOPERATOR_H

#include "Expressions.h"
#include "DataHandlers/DataManager.h"

/**
 * UnaryOperator class
 */
class UnaryOperator : public Expression {
protected:
    Expression* exp;
public:
    UnaryOperator(Expression* exp);
    ~UnaryOperator() override;
};


#endif //EX3_NEW_UNARYOPERATOR_H
