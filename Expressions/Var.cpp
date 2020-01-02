
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

//Ctor of variable from simulator
Var::Var(string inputSim, bool inputRecv) {
    this->sim = inputSim;
    this->recv = inputRecv;
    this->val = 0;
    this->hasNameFlag = true;
}

string Var::getSim() {
    return this->sim;
}

double Var::getFlatValue() {
    return  this->val;
}

double Var::calculate() {
    DataManager *m = DataManager::getInstance();
    double value;
    if(this->sim == "") {
        return this->getFlatValue();
    }
    value = m->getMapValue(this->sim);
    return value;
}

bool Var::isRecieving() {
    return this->recv;
}

void Var::setValue(double newVal) {
    this->val = newVal;
}

bool Var::hasName() {
    return this->hasNameFlag;
}