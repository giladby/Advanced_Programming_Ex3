
#ifndef EX3_NEW_DATAMANAGER_H
#define EX3_NEW_DATAMANAGER_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include <atomic>
#include "Expressions/Var.h"
#include "Expressions/Expressions.h"
#include "Commands/Command.h"
#include "Interpreter.h"
#include "Commands/FuncCommand.h"

using namespace std;

/**
* DataManager class
* This class has only one object created during the program.
* It holds all the relevant data.
*/
class DataManager {
private:
    static DataManager* manager;
    unordered_map<string,Var*> varsMap;
    unordered_map<string,double> simsMap;
    unordered_map<string, Command*> commandsMap;
    unordered_map<string, Func*> funcMap;
    vector<string> simsVector;
    Interpreter* inter;
    mutex mutexLock;
    int simulatorSocket;
    int clientSocket;
    string stringToSend;
    bool sending;
    atomic<bool> done;
public:
    DataManager();
    ~DataManager();
    unordered_map<string,Var*>* getVarsMap();
    unordered_map<string,Func*>* getFuncMap();
    unordered_map<string,double>* getSimsMap();
    unordered_map<string, Command*>* getCommandsMap();
    Interpreter* getInter();
    void changeSim(string simString, double newVal);
    void addCommand(string commandString, Command* inputCommand);
    void addCommands();
    void deleteCommands();
    void deleteVars();
    void deleteFuncs();
    void deleteAllMaps();
    static DataManager* getInstance();
    void setSimsVector();
    void updateSimsValues(vector<string> values);
    double getMapValue(string sim);
    int getSimulatorSocket();
    void changeSimulatorSocket(int val);
    int getClientSocket();
    void changeClientSocket(int val);
    void initSimsMap();
    string getStringToSend();
    void setStringToSend(string str);
    bool getSending();
    void switchSending();
    bool isDone();
    void setDone();
    void addFunc(vector<string> strings, string funcName, string varName);
    bool isFunc(string funcName);
    thread serverThread;
    thread clientThread;
};


#endif //EX3_NEW_DATAMANAGER_H
