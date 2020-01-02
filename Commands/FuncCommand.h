
#ifndef EX3_NEW_FUNCCOMMAND_H
#define EX3_NEW_FUNCCOMMAND_H

#include "Command.h"

/**
* FuncCommand Class
*/
class FuncCommand : public Command {
private:

public:
    int execute(vector<string> strings, int index);
    int dummyExecute(vector<string> strings, int index);
};

/**
* Func Class
*/
class Func {
private:
    vector<string> commands;
    string var;

public:
    Func(vector<string> inputCommands, string inputVar);
    void operate(string valueToReplace);
    vector<string> updatedVector(string newValue);

};


#endif //EX3_NEW_FUNCCOMMAND_H
