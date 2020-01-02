
#include "LoopCommand.h"

//check if the condition is true, and if so - operate the body statement over and over again, until the condition is false
int LoopCommand::execute(vector<string> strings, int index) {
    int returnedIndex = index;
    Command* c;
    DataManager *m = DataManager::getInstance();
    unordered_map<string,Command*>* commandMap = m->getCommandsMap();
    Interpreter* inter = m->getInter();
    string condition = strings[index + 2];
    Condition* cond = new Condition(inter->interpret(strings[index + 1]), inter->interpret(strings[index + 3]), condition);
    //increase returned index for condition (if + left + condition + right)
    returnedIndex += 5;
    int temp = returnedIndex;
    while(true) {
        returnedIndex = temp;
        //if the condition is true - operate the body statement
        if(cond->getCondition()) {
            while(strings[returnedIndex] != "}") {
                if(this->isContainCommand(commandMap, strings[returnedIndex])) {
                    c = this->getCommand(commandMap, strings[returnedIndex]);
                    returnedIndex = c->execute(strings, returnedIndex);
                } else {
                    if(m->isFunc(strings[returnedIndex])) {
                        (*m->getFuncMap())[strings[returnedIndex]]->operate(strings[returnedIndex + 1]);
                        returnedIndex++;
                    }
                    returnedIndex++;
                }
            }
        //if the condition is false - skip the body statement
        } else {
            while(strings[returnedIndex] != "}") {
                if(this->isContainCommand(commandMap, strings[returnedIndex])) {
                    c = this->getCommand(commandMap, strings[returnedIndex]);
                    returnedIndex = c->dummyExecute(strings, returnedIndex);
                } else {
                    if(m->isFunc(strings[returnedIndex])) {
                        // plus 1 for the function call, and then another plus 1 for the input value
                        returnedIndex++;
                    }
                    returnedIndex++;
                }
            }
            break;
        }
    }
    delete cond;
    // increase returned index by 1 (for next)
    return returnedIndex + 1;
}

//skip over the loop body, don't even check the condition
int LoopCommand::dummyExecute(vector<string> strings, int index) {
    int returnedIndex = index;
    Command* c;
    DataManager *m = DataManager::getInstance();
    unordered_map<string,Command*>* commandMap = m->getCommandsMap();
    //increase returned index for condition (while + left + condition + right)
    returnedIndex += 5;
    while(strings[returnedIndex] != "}") {
        if(this->isContainCommand(commandMap, strings[returnedIndex])) {
            c = this->getCommand(commandMap, strings[returnedIndex]);
            returnedIndex = c->dummyExecute(strings, returnedIndex);
        } else {
            if(m->isFunc(strings[returnedIndex])) {
                // plus 1 for the function call, and then another plus 1 for the input value
                returnedIndex++;
            }
            returnedIndex++;
        }
    }
    // increase returned index by 1 (for next)
    return returnedIndex + 1;
}
