//
// Created by yuvalkit on 16/12/2019.
//
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ControlClient.h"
using namespace std;

#define PORT 5402
void ControlClient::connectToSimulator() {
    //create socket
    this->client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address{}; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
    address.sin_port = htons(PORT);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(this->client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        return;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }



}
void ControlClient::sendToSimulator() {
    string str = "set controls/flight/rudder -1\r\n";
    int is_sent = send(this->client_socket , str.c_str(), str.size(), 0);
    if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    } else {
        std::cout<<"message sent to server" <<std::endl;
    }
}

