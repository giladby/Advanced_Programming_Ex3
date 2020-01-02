
#include "BinaryOperator.h"

// BinaryOperator class methods

BinaryOperator::BinaryOperator(Expression *inputLeft, Expression *inputRight) {
    this->left = inputLeft;
    this->right = inputRight;
}

BinaryOperator::~BinaryOperator() {
    if(this->right != nullptr) {
        if (dynamic_cast<Var*>(this->right) != nullptr) {
            if (!dynamic_cast<Var*>(this->right)->hasName()) {
                delete this->right;
            }
        } else {
            delete this->right;
        }
    }
    if(this->left != nullptr) {
        if (dynamic_cast<Var*>(this->left) != nullptr) {
            if (!dynamic_cast<Var*>(this->left)->hasName()) {
                delete this->left;
            }
        } else {
            delete this->left;
        }
    }
}