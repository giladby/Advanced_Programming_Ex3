
#include "UnaryOperator.h"

// UnaryOperator class methods

UnaryOperator::UnaryOperator(Expression *inputExp) {
    this->exp = inputExp;
}

UnaryOperator::~UnaryOperator() {
    if(this->exp != nullptr) {
        if (dynamic_cast<Var*>(this->exp) != nullptr) {
            if (!dynamic_cast<Var*>(this->exp)->hasName()) {
                delete this->exp;
            }
        } else {
            delete this->exp;
        }
    }
}