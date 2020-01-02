
#ifndef EX3_NEW_INTERPRETER_H
#define EX3_NEW_INTERPRETER_H

#include "../Expressions/Var.h"
#include <queue>
#include "string"
#include "unordered_map"

/**
 * Interpreter class
 */
class Interpreter {
private:
    unordered_map<string, Var*>* varsMap;
    int getPrecedence(char c);
    bool isParenthesisOk(string str);
    bool isVariableHasValue(string str);
    bool isSyntaxOk(string str);
    bool isOperator(char c);
    bool properVariable(string str);
    bool isUnaryOperator(char c);
    queue<string> toQueue(string str);
    Expression* makeAnExpression(string str);

public:
    void setMap(unordered_map<string, Var*>* inputVarsMap);
    Expression* interpret(string str);
    bool properNumber(string str);
};


#endif //EX3_NEW_INTERPRETER_H
