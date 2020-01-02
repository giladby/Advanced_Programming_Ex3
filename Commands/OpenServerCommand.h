
#ifndef EX3_NEW_OPENSERVERCOMMAND_H
#define EX3_NEW_OPENSERVERCOMMAND_H

#include "Command.h"
#include "thread"
#include "../DataHandlers/DataManager.h"

/**
* OpenServerCommand Class
*/
class OpenServerCommand : public Command {
private:
    int port;
    thread t;
    void connectToSimulator();
public:
    int execute(vector<string> strings, int index);
    int dummyExecute(vector<string> strings, int index);
    static void recvFromSimulator();
};


#endif //EX3_NEW_OPENSERVERCOMMAND_H
