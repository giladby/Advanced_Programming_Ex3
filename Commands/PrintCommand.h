
#ifndef EX3_NEW_PRINTCOMMAND_H
#define EX3_NEW_PRINTCOMMAND_H

#include "Command.h"
#include "../DataHandlers/DataManager.h"

/**
* PrintCommand Class
*/
class PrintCommand : public Command {
private:

public:
    int execute(vector<string> strings, int index);
    int dummyExecute(vector<string> strings, int index);
};


#endif //EX3_NEW_PRINTCOMMAND_H
