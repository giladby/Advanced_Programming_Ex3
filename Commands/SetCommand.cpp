
#include "SetCommand.h"
#include "../Expressions/Var.h"

//skip the setting
int SetCommand::dummyExecute(vector<string> strings, int index) {
    if (strings.empty()) {
        cerr << "There are no strings"<<endl;
    }
    // increase returned index by 2 (the expression to set + 1 for next)
    return index + 2;
}

//set the new value to the relevant var, if needed - update the simulator
int SetCommand::execute(vector<string> strings, int index) {
    Var* v1;
    Expression* v2;
    DataManager *m = DataManager::getInstance();
    unordered_map<string,Var*>* varMap = m->getVarsMap();
    Interpreter* inter = m->getInter();
    string strToSend;
    double newValue;
    string varName = strings[index - 1];
    if(this->isContainVar(varMap, varName)) {
        v1 = (*varMap)[varName];
    } else {
        cerr << "this var is not defined in variable's map" << endl;
        exit(1);
    }
    v2 = inter->interpret(strings[index + 1]);
    newValue = v2->calculate();
    // delete v2 only if it's not a var with a name
    if (dynamic_cast<Var*>(v2) != nullptr) {
        if (!dynamic_cast<Var*>(v2)->hasName()) {
            delete v2;
        }
    } else {
        delete v2;
    }
    // if the var has no sim
    if(v1->getSim() == "") {
        v1->setValue(newValue);
    } else {
        if(!v1->isRecieving()) {
            // update simulator
            m->changeSim(v1->getSim(), newValue);
            // make the str to send to the simulator
            strToSend = "set " + v1->getSim() + " " + to_string(newValue) + "\r\n";
            m->setStringToSend(strToSend);
            // make the sending flag true
            m->switchSending();
        }
    }
    // increase returned index by 2 (the expression to set + 1 for next)
    return index + 2;
}

