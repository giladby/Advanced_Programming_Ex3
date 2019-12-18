//
// Created by yuvalkit on 16/12/2019.
//

#include "DataServer.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

#define PORT 5400
/**
 * DataServer Class
 */
void DataServer::connectToSimulator() {
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
    address.sin_port = htons(PORT);
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        return;
    }
    if (listen(socketfd, 5) == -1) {
        std::cerr<<"Error during listening command"<<std::endl;
        return;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }
    this->simulatorSocket = accept(socketfd, (struct sockaddr *)&address, (socklen_t*)&address);
    if (this->simulatorSocket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
        return;
    }
    cout << "connected" << endl;
    close(socketfd);



}
void DataServer::recvFromSimulator() {
    //reading from client
    char buffer[1024] = {0};
    int data = read(this->simulatorSocket , buffer, 1024);
    while (data != -1) {
        cout<<buffer<<endl;
        data = read(this->simulatorSocket , buffer, 1024);
    }

}