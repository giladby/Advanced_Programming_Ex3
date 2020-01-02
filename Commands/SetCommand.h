
#ifndef EX3_NEW_SETCOMMAND_H
#define EX3_NEW_SETCOMMAND_H

#include "Command.h"
#include "DataHandlers/DataManager.h"

/**
* SetCommand Class
*/
class SetCommand : public Command {
private:

public:
    int execute(vector<string> strings, int index);
    int dummyExecute(vector<string> strings, int index);
};


#endif //EX3_NEW_SETCOMMAND_H
