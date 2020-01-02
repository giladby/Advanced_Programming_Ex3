
#include "UnaryOperator.h"

// UnaryOperator class methods

UnaryOperator::UnaryOperator(Expression *inputExp) {
    this->exp = inputExp;
}

UnaryOperator::~UnaryOperator() {
    if(this->exp != nullptr) {
        //check if the inner exp is var
        if (dynamic_cast<Var*>(this->exp) != nullptr) {
            //check if the inner exp hasn't name (it is constant) and delete it
            if (!dynamic_cast<Var*>(this->exp)->hasName()) {
                delete this->exp;
            }
        } else {
            delete this->exp;
        }
    }
}