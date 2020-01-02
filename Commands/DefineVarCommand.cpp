
#include "DefineVarCommand.h"
#include "../Expressions/Var.h"

//create new var and save it in vars map, if it should be saved there
int DefineVarCommand::execute(vector<string> strings, int index) {
    int returnedIndex = index + 1;
    DataManager *m = DataManager::getInstance();
    unordered_map<string,Var*>* varMap = m->getVarsMap();
    Interpreter* inter = m->getInter();
    Expression* v2;
    Var* newVar;
    string varName = strings[returnedIndex];
    //check the var is not already exist in map
    if(this->isContainVar(varMap, varName)) {
        cerr << "this var is already defined in variable's map" << endl;
        exit(1);
    }
    returnedIndex++;
    if(strings[returnedIndex] == "=") {
        v2 = inter->interpret(strings[returnedIndex + 1]);
        newVar = new Var(v2->calculate(), true);
        if (dynamic_cast<Var*>(v2) != nullptr) {
            if (!dynamic_cast<Var*>(v2)->hasName()) {
                delete v2;
            }
        } else {
            delete v2;
        }
    } else {
        if(strings[returnedIndex] == "->" && strings[returnedIndex + 1] == "sim") {
            newVar = new Var(strings[returnedIndex + 2], false);
            returnedIndex++;
        } else {
            if(strings[returnedIndex] == "<-" && strings[returnedIndex + 1] == "sim") {
                newVar = new Var(strings[returnedIndex + 2], true);
                returnedIndex++;
            } else {
                cerr << "wrong input, this Var defining is wrong" << endl;
                exit(1);
            }
        }
    }
    this->addVar(varMap, newVar, varName);
    // increase the returned index by 2 (1 for the ' " '/ ' -> '/ ' <- ', and 1 more for the sim/value).
    // (in case of 'sim', in the end of the if condition checked that the sim case,
    // we have already increase the retuned index by 1,
    // so in each ' = '/ ' -> '/ ' <- ' case we will have to increase the index by 2)
    return returnedIndex + 2;
}

//skip over the defining operation
int DefineVarCommand::dummyExecute(vector<string> strings, int index) {
    int returnedIndex = index + 2;
    if(strings[returnedIndex] == "=") {
        // increase the returned index by 2 (1 for the ' " ', and 1 more for the value)
        return returnedIndex + 2;
    } else {
        if(strings[returnedIndex] == "<-" || strings[returnedIndex] == "->") {
            // increase the returned index by 2
            // (1 for the ' -> '/ ' <- ', 1 more for the sim word, and 1 more for the sim value).
            return returnedIndex + 3;
        } else {
            cerr << "wrong input, this Var defining is wrong" << endl;
            exit(1);
        }
    }
}
