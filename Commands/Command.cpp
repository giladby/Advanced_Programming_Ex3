
#include "Command.h"
#include <string>

/**
* Condition class
*/

Condition::Condition(Expression* var1, Expression* var2, string condition) {
    this->v1 = var1;
    this->v2 = var2;
    this->cond = condition;
}
// delete the expressions unless the expression is a var with a name, then the DataManager will delete it at the end
Condition::~Condition() {
    if (dynamic_cast<Var*>(this->v1) != nullptr) {
        if (!dynamic_cast<Var*>(this->v1)->hasName()) {
            delete this->v1;
        }
    } else {
        delete this->v1;
    }
    if (dynamic_cast<Var*>(this->v2) != nullptr) {
        if (!dynamic_cast<Var*>(this->v2)->hasName()) {
            delete this->v2;
        }
    } else {
        delete this->v2;
    }
}

//check and return the condition status
bool Condition::getCondition() {
    if(this->cond == "==") {
        return this->v1->calculate() == this->v2->calculate();
    }
    if(this->cond == ">=") {
        return this->v1->calculate() >= this->v2->calculate();
    }
    if(this->cond == "<=") {
        return this->v1->calculate() <= this->v2->calculate();
    }
    if(this->cond == "!=") {
        return this->v1->calculate() != this->v2->calculate();
    }
    if(this->cond == "<") {
        return this->v1->calculate() < this->v2->calculate();
    }
    if(this->cond == ">") {
        return this->v1->calculate() > this->v2->calculate();
    }
    return false;
}

/**
* Command class
*/

//check if the commands map contains the given command name
bool Command::isContainCommand(unordered_map<string, Command* >* commandMap, string str) {
    return (*commandMap).count(str) > 0;
}

// return the asked command from the command map
class Command * Command::getCommand(unordered_map<string, class Command *> * commandMap, string str) {
    return (*commandMap)[str];
}

//check if the vars map contains the given var name
bool Command::isContainVar(unordered_map<string, class Var *> * varMap, string str) {
    return (*varMap).count(str) > 0;
}

//adds a new var to vars map
void Command::addVar(unordered_map<string, class Var *>* varMap, class Var * newVar, string str) {
    (*varMap)[str] = newVar;
}
