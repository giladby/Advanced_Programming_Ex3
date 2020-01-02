
#ifndef EX3_NEW_COMMAND_H
#define EX3_NEW_COMMAND_H

#include <iostream>
#include <vector>
#include <string>
#include "Expressions/Expressions.h"
#include "DataHandlers/Interpreter.h"

using namespace std;

/**
* Condition class
*/

class Condition {
private:
    Expression* v1;
    Expression* v2;
    string cond;
public:
    Condition(Expression* var1, Expression* var2, string condition);
    bool getCondition();
    ~Condition();
};

/**
* Commands Interface
*/
class Command {
public:
    virtual int execute(vector<string> strings, int index) = 0;
    virtual int dummyExecute(vector<string> strings, int index) = 0;
    bool isContainCommand(unordered_map<string, Command* >* commandMap, string str);
    Command* getCommand(unordered_map<string, Command* >* commandMap, string str);
    bool isContainVar(unordered_map<string, class Var *> * varMap, string str);
    void addVar(unordered_map<string, class Var *>* varMap, class Var * newVar, string str);
    virtual ~Command() {}
};




















#endif //EX3_NEW_COMMAND_H
