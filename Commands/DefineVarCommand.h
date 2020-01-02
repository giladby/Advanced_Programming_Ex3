
#ifndef EX3_NEW_DEFINEVARCOMMAND_H
#define EX3_NEW_DEFINEVARCOMMAND_H

#include "Command.h"
#include "../DataHandlers/DataManager.h"

/**
* DefineVarCommand Class
*/
class DefineVarCommand : public Command {
private:

public:
    int execute(vector<string> strings, int index);
    int dummyExecute(vector<string> strings, int index);
};


#endif //EX3_NEW_DEFINEVARCOMMAND_H
