
#include "Var.h"
#include "../DataHandlers/DataManager.h"

// Var class methods

Var::Var() {
    this->sim = "";
    this->recv = false;
    this->val = 0;
}

//Ctor for constant
Var::Var(double inputVal, bool inputHasNameFlag) {
    this->sim = "";
    this->recv = false;
    this->val = inputVal;
    this->hasNameFlag = inputHasNameFlag;
}

//Ctor of variable of simulator
Var::Var(string inputSim, bool inputRecv) {
    this->sim = inputSim;
    this->recv = inputRecv;
    this->val = 0;
    this->hasNameFlag = true;
}

//get the sim string
string Var::getSim() {
    return this->sim;
}

//get the value the variable holds
double Var::getFlatValue() {
    return  this->val;
}

//calculate the variable value
double Var::calculate() {
    DataManager *m = DataManager::getInstance();
    double value;
    //if this variable isn't in map
    if(this->sim == "") {
        return this->getFlatValue();
    }
    //search the relevant value in map
    value = m->getMapValue(this->sim);
    return value;
}

// this var value has to be updated by the simulator
bool Var::isRecieving() {
    return this->recv;
}

//change the value the variable holds
void Var::setValue(double newVal) {
    this->val = newVal;
}

//check if the variable ahs name
bool Var::hasName() {
    return this->hasNameFlag;
}