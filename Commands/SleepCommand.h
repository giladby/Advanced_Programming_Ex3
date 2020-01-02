
#ifndef EX3_NEW_SLEEPCOMMAND_H
#define EX3_NEW_SLEEPCOMMAND_H

#include "Command.h"
#include "DataHandlers/DataManager.h"

/**
* SleepCommand Class
*/
class SleepCommand : public Command {
private:

public:
    int execute(vector<string> strings, int index);
    int dummyExecute(vector<string> strings, int index);
};


#endif //EX3_NEW_SLEEPCOMMAND_H
