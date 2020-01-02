
#include <unistd.h>
#include "DataManager.h"
#include "Commands/PrintCommand.h"
#include "Commands/SetCommand.h"
#include "Commands/DefineVarCommand.h"
#include "Commands/SleepCommand.h"
#include "Commands/OpenServerCommand.h"
#include "Commands/LoopCommand.h"
#include "Commands/IfCommand.h"
#include "Commands/ConnectCommand.h"
#include "Commands/FuncCommand.h"

DataManager* DataManager::manager = 0;

DataManager::DataManager() {
    this->inter = new Interpreter();
    this->inter->setMap(&this->varsMap);
    this->addCommands();
    this->setSimsVector();
    this->initSimsMap();
    this->done = false;
    this->sending = false;
}

DataManager::~DataManager() {
    // close the opened sockets
    this->clientThread.join();
    this->serverThread.join();
    close(this->clientSocket);
    close(this->simulatorSocket);
    delete this->inter;
    this->deleteAllMaps();
}

class DataManager* DataManager::getInstance() {
    if(!manager) {
        manager = new DataManager();
    }
    return manager;
}

//send the command map by reference
unordered_map<string, class Command *>* DataManager::getCommandsMap() {
    return &this->commandsMap;
}

//send the vars map by reference
unordered_map<string, class Var *>* DataManager::getVarsMap() {
    return &this->varsMap;
}

//send the sims value map by reference
unordered_map<string, double>* DataManager::getSimsMap() {
    return &this->simsMap;
}

//change value of 'simsString' key in sims value map
void DataManager::changeSim(string simString,double newVal) {
    this->mutexLock.lock();
    this->simsMap[simString] = newVal;
    this->mutexLock.unlock();
}

//send sim's value
double DataManager::getMapValue(string sim) {
    double value;
    this->mutexLock.lock();
    value = this->simsMap[sim];
    this->mutexLock.unlock();
    return value;
}

//add new command to the commands map
void DataManager::addCommand(string commandString, Command* inputCommand) {
    this->commandsMap[commandString] = inputCommand;
}

//add all commands to the commands map
void DataManager::addCommands() {
    this->addCommand("Print", new PrintCommand());
    this->addCommand("=", new SetCommand());
    this->addCommand("var", new DefineVarCommand());
    this->addCommand("while", new LoopCommand());
    this->addCommand("if", new IfCommand());
    this->addCommand("Sleep", new SleepCommand());
    this->addCommand("openDataServer", new OpenServerCommand());
    this->addCommand("connectControlClient", new ConnectCommand());
    this->addCommand("{", new FuncCommand());
}

//delete commands map
void DataManager::deleteCommands() {
    for (auto it = this->commandsMap.begin(); it != this->commandsMap.end(); ++it) {
         delete it->second;
    }
}

//delete vars map
void DataManager::deleteVars() {
    for (auto it = this->varsMap.begin(); it != this->varsMap.end(); ++it) {
        delete it->second;
    }
}

//delete functions map
void DataManager::deleteFuncs() {
    for (auto it = this->funcMap.begin(); it != this->funcMap.end(); ++it) {
        delete it->second;
    }
}

//delete all maps
void DataManager::deleteAllMaps() {
    this->deleteVars();
    this->deleteCommands();
    this->deleteFuncs();
}

//send the interpreter by reference
class Interpreter * DataManager::getInter() {
    return this->inter;
}

//set the sims value map
void DataManager::setSimsVector() {
    this->simsVector.emplace_back("/instrumentation/airspeed-indicator/indicated-speed-kt");
    this->simsVector.emplace_back("/sim/time/warp");
    this->simsVector.emplace_back("/controls/switches/magnetos");
    this->simsVector.emplace_back("/instrumentation/heading-indicator/offset-deg");
    this->simsVector.emplace_back("/instrumentation/altimeter/indicated-altitude-ft");
    this->simsVector.emplace_back("/instrumentation/altimeter/pressure-alt-ft");
    this->simsVector.emplace_back("/instrumentation/attitude-indicator/indicated-pitch-deg");
    this->simsVector.emplace_back("/instrumentation/attitude-indicator/indicated-roll-deg");
    this->simsVector.emplace_back("/instrumentation/attitude-indicator/internal-pitch-deg");
    this->simsVector.emplace_back("/instrumentation/attitude-indicator/internal-roll-deg");
    this->simsVector.emplace_back("/instrumentation/encoder/indicated-altitude-ft");
    this->simsVector.emplace_back("/instrumentation/encoder/pressure-alt-ft");
    this->simsVector.emplace_back("/instrumentation/gps/indicated-altitude-ft");
    this->simsVector.emplace_back("/instrumentation/gps/indicated-ground-speed-kt");
    this->simsVector.emplace_back("/instrumentation/gps/indicated-vertical-speed");
    this->simsVector.emplace_back("/instrumentation/heading-indicator/indicated-heading-deg");
    this->simsVector.emplace_back("/instrumentation/magnetic-compass/indicated-heading-deg");
    this->simsVector.emplace_back("/instrumentation/slip-skid-ball/indicated-slip-skid");
    this->simsVector.emplace_back("/instrumentation/turn-indicator/indicated-turn-rate");
    this->simsVector.emplace_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    this->simsVector.emplace_back("/controls/flight/aileron");
    this->simsVector.emplace_back("/controls/flight/elevator");
    this->simsVector.emplace_back("/controls/flight/rudder");
    this->simsVector.emplace_back("/controls/flight/flaps");
    this->simsVector.emplace_back("/controls/engines/engine/throttle");
    this->simsVector.emplace_back("/controls/engines/current-engine/throttle");
    this->simsVector.emplace_back("/controls/switches/master-avionics");
    this->simsVector.emplace_back("/controls/switches/starter");
    this->simsVector.emplace_back("/engines/active-engine/auto-start");
    this->simsVector.emplace_back("/controls/flight/speedbrake");
    this->simsVector.emplace_back("/sim/model/c172p/brake-parking");
    this->simsVector.emplace_back("/controls/engines/engine/primer");
    this->simsVector.emplace_back("/controls/engines/current-engine/mixture");
    this->simsVector.emplace_back("/controls/switches/master-bat");
    this->simsVector.emplace_back("/controls/switches/master-alt");
    this->simsVector.emplace_back("/engines/engine/rpm");
}

//initialize the sims value map
void DataManager::initSimsMap() {
    for (unsigned int i = 0; i < this->simsVector.size(); i++) {
        this->simsMap[this->simsVector[i]] = 0;
    }
}

//update the sims value map,according the given simulator's information
void DataManager::updateSimsValues(vector<string> values) {
    this->mutexLock.lock();
    for (unsigned int i = 0; i < values.size(); i++) {
        if(this->inter->properNumber(values[i])) {
            this->simsMap[this->simsVector[i]] = strtod(values[i].c_str(), NULL);
        }
    }
    this->mutexLock.unlock();
}

// return the simulator's server socket number
int DataManager::getSimulatorSocket() {
    return this->simulatorSocket;
}

// change the simulator's server socket number
void DataManager::changeSimulatorSocket(int val) {
    this->simulatorSocket = val;
}

// return the simulator's client socket number
int DataManager::getClientSocket() {
    return this->clientSocket;
}

// change the simulator's client socket number
void DataManager::changeClientSocket(int val) {
    this->clientSocket = val;
}

string DataManager::getStringToSend() {
    return this->stringToSend;
}

bool DataManager::getSending() {
    return this->sending;
}

void DataManager::setStringToSend(string str) {
    this->stringToSend = str;
}

void DataManager::switchSending() {
    this->sending = !this->sending;
}

bool DataManager::isDone() {
    return this->done;
}

//set the boolean flag to true, the reading of file is end
void DataManager::setDone() {
    this->done = true;
}

//add new function to functions map
void DataManager::addFunc(vector<string> strings, string funcName, string varName) {
    if(this->funcMap.find(funcName) != this->funcMap.end()) {
        cerr << "func already exist" << endl;
        exit(1);
    }
    this->funcMap[funcName] = new Func(strings,varName);
}

//check if the given function is contained in the functions map
bool DataManager::isFunc(string funcName) {
    return this->funcMap.find(funcName) != this->funcMap.end();
}

//send the function map by reference
unordered_map<string, Func *>* DataManager::getFuncMap() {
    return &this->funcMap;
}