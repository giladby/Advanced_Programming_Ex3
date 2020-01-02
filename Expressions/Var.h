
#ifndef EX3_NEW_VAR_H
#define EX3_NEW_VAR_H

#include "Expressions.h"

/**
* Var class
*/
class Var : public Expression {
private:
    string sim;
    double val;
    bool recv;
    bool hasNameFlag;
public:
    Var();
    Var(string inputSim, bool inputRecv);
    Var(double inputVal, bool inputHasNameFlag);
    bool isRecieving();
    string getSim();
    double getFlatValue();
    double calculate();
    void setValue(double newVal);
    bool hasName();
};


#endif //EX3_NEW_VAR_H
