
#ifndef EX3_NEW_LOOPCOMMAND_H
#define EX3_NEW_LOOPCOMMAND_H

#include "Command.h"
#include "../DataHandlers/DataManager.h"

/**
* LoopCommand Class
*/
class LoopCommand : public Command {
private:

public:
    int execute(vector<string> strings, int index);
    int dummyExecute(vector<string> strings, int index);
};


#endif //EX3_NEW_LOOPCOMMAND_H
