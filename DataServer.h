//
// Created by yuvalkit on 16/12/2019.
//

#ifndef AP_EX3_DATASERVER_H
#define AP_EX3_DATASERVER_H

/**
 * DataServer Class
 */
class DataServer {
public:
    int simulatorSocket;
public:
    void connectToSimulator();
    void recvFromSimulator();

};


#endif //AP_EX3_DATASERVER_H
