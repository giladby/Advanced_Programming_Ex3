
#include "OpenServerCommand.h"
#include "../DataHandlers/DataManager.h"
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include "../DataHandlers/Lexer.h"

//connect to the simulator's server, and save the socket number
int OpenServerCommand::execute(vector<string> strings, int index) {
    DataManager* manager = DataManager::getInstance();
    int returnIndex = index + 1;
    Expression* exp = manager->getInter()->interpret(strings[returnIndex]);
    this->port = (int) exp->calculate();
    delete exp;
    thread serverThread(&OpenServerCommand::connectToSimulator, this);
    serverThread.join();
    manager->serverThread = thread(recvFromSimulator);
    // increase returned index by 1 for next
    return returnIndex + 1;
}

//skip over the connection
int OpenServerCommand::dummyExecute(vector<string> strings, int index) {
    if (strings.empty()) {
        cerr << "There are no strings"<<endl;
    }
    // increase returned index by 3 (server + 1 for port)
    return index + 2;
}

//connect once again to simulator, and stay connected for receiving data
void OpenServerCommand::connectToSimulator() {
    DataManager* manager = DataManager::getInstance();
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        cerr << "Could not create a socket"<<endl;
        return;
    }
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->port);
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<endl;
        return;
    }
    if (listen(socketfd, 5) == -1) {
        std::cerr<<"Error during listening command"<<endl;
        return;
    }
    manager->changeSimulatorSocket(accept(socketfd, (struct sockaddr *)&address, (socklen_t*)&address));
    if (manager->getSimulatorSocket() == -1) {
        std::cerr<<"Error accepting client"<<endl;
        return;
    }
    close(socketfd);
}

//receive data from simulator, and update the relevant values according it
void OpenServerCommand::recvFromSimulator() {
    Lexer lexer;
    char testChar;
    bool validFlag;
    int counterValid;
    char buffer[1024] = {0};
    vector<string> bufferVector;
    vector<string> valuesVector;
    string current = "", substr, testStr, str, temp;
    DataManager* manager = DataManager::getInstance();
    int data = read(manager->getSimulatorSocket(), buffer, 1024);
    while (data != -1) {
        if (manager->isDone()) {
            break;
        }
        validFlag = true;
        current += buffer;
        temp = current;
        bufferVector = lexer.split(current, "\n");
        for (unsigned int j = 0; j < bufferVector.size(); j++) {
            str = bufferVector[j];
            counterValid = 0;
            if(str == "") {
                break;
            }
            //the last chunk is cut sometimes, and if so - run over the chunk and remove the bad characters.
            if(j == bufferVector.size() - 1) {
                for(unsigned int i = 0; i < str.length(); i++) {
                    testChar = str[i];
                    if(isdigit(testChar) || testChar == '.' || testChar == ','|| testChar == '-') {
                        counterValid++;
                    } else {
                        validFlag = false;
                        break;
                    }
                }
                if(!validFlag) {
                    current = str.substr(0, counterValid);
                    break;
                }
            }
            valuesVector = lexer.split(str, ",");
            if(valuesVector.size() == 36) {
                manager->updateSimsValues(valuesVector);
            }
            current = "";
        }
        data = read(manager->getSimulatorSocket(), buffer, 1024);
    }
}
