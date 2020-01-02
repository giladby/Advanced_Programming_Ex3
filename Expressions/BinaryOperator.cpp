
#include "BinaryOperator.h"

// BinaryOperator class methods

BinaryOperator::BinaryOperator(Expression *inputLeft, Expression *inputRight) {
    this->left = inputLeft;
    this->right = inputRight;
}

BinaryOperator::~BinaryOperator() {
    //check if the first inner exp is var
    if(this->right != nullptr) {
        if (dynamic_cast<Var*>(this->right) != nullptr) {
            //check if the first inner exp hasn't name (it is constant) and delete it
            if (!dynamic_cast<Var*>(this->right)->hasName()) {
                delete this->right;
            }
        } else {
            delete this->right;
        }
    }
    //check if the second inner exp is var
    if(this->left != nullptr) {
        if (dynamic_cast<Var*>(this->left) != nullptr) {
            //check if the second inner exp hasn't name (it is constant) and delete it
            if (!dynamic_cast<Var*>(this->left)->hasName()) {
                delete this->left;
            }
        } else {
            delete this->left;
        }
    }
}