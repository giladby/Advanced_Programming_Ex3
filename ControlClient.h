//
// Created by yuvalkit on 16/12/2019.
//

#ifndef AP_EX3_CONTROLCLIENT_H
#define AP_EX3_CONTROLCLIENT_H


class ControlClient {
private:
    int client_socket;
public:
    void connectToSimulator();
    void sendToSimulator();
};


#endif //AP_EX3_CONTROLCLIENT_H
