
#include "ConnectCommand.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../DataHandlers/DataManager.h"
#include <thread>

using namespace std;

// connect the simulator's socket, and the connect again and stay connected for sending data
int ConnectCommand::execute(vector<string> strings, int index) {
    DataManager* manager = DataManager::getInstance();
    int returnIndex = index + 1;
    this->ip = strings[returnIndex];
    // get the expression of the port and then calculate it
    Expression* exp = manager->getInter()->interpret(strings[returnIndex + 1]);
    this->port = (int) exp->calculate();
    delete exp;
    // blocking call of the client connection
    thread clientThread(&ConnectCommand::connectToSimulator, this);
    clientThread.join();
    // does the send to simulator thread in the background
    manager->clientThread = thread(sendToSimulator);
    // increase returned index by 1 for next
    return returnIndex + 2;
}

// skip over the connection
int ConnectCommand::dummyExecute(vector<string> strings, int index) {
    if (strings.empty()) {
        cerr << "There are no strings"<<endl;
    }
    // increase returned index by 3 (connect + 2 for port and ip)
    return index + 3;
}

// connect the simulator's socket, and save the socket number
void ConnectCommand::connectToSimulator() {
    DataManager* manager = DataManager::getInstance();
    // create socket
    manager->changeClientSocket(socket(AF_INET, SOCK_STREAM, 0));
    if (manager->getClientSocket() == -1) {
        //error
        cerr << "Could not create a socket" << endl;
        return;
    }

    // we need to create a sockaddr obj to hold address of server
    sockaddr_in address{}; //in means IP4
    address.sin_family = AF_INET; //IP4
    address.sin_addr.s_addr = inet_addr(this->ip.c_str()); //get the ip
    address.sin_port = htons(this->port); // get the ip

    // requesting a connection with the server
    int is_connect = connect(manager->getClientSocket(), (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        cerr << "Could not connect to host server" << endl;
        return;
    }
}

// connect the simulator's socket for sending data to simulator
void ConnectCommand::sendToSimulator() {
    DataManager* manager = DataManager::getInstance();
    string data;
    // until the program ends
    while (!manager->isDone()) {
        // if there is data to send
        if (manager->getSending()) {
            data = manager->getStringToSend();
            // send to simulator
            int is_sent = send(manager->getClientSocket() , data.c_str(), data.size(), 0);
            if (is_sent == -1) {
                cerr << "Error sending message" << endl;
                exit(1);
            } else {
                manager->switchSending();
            }
        }
    }
}
