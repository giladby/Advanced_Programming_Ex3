
#ifndef EX3_NEW_CONNECTCOMMAND_H
#define EX3_NEW_CONNECTCOMMAND_H

#include "Command.h"
#include <thread>
#include "../DataHandlers/DataManager.h"

/**
* ConnectCommand Class
*/
class ConnectCommand : public Command {
private:
    string ip;
    int port;
    thread t;
public:
    int execute(vector<string> strings, int index);
    int dummyExecute(vector<string> strings, int index);
    void connectToSimulator();
    static void sendToSimulator();

};


#endif //EX3_NEW_CONNECTCOMMAND_H
