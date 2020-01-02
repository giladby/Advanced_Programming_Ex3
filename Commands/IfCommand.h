
#ifndef EX3_NEW_IFCOMMAND_H
#define EX3_NEW_IFCOMMAND_H

#include "Command.h"
#include "../DataHandlers/DataManager.h"

/**
* IfCommand Class
*/
class IfCommand : public Command {
private:

public:
    int execute(vector<string> strings, int index);
    int dummyExecute(vector<string> strings, int index);
};


#endif //EX3_NEW_IFCOMMAND_H
