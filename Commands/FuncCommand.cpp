
#include "FuncCommand.h"
#include "../DataHandlers/Parser.h"
#include "../DataHandlers/DataManager.h"

//skip over the declaration of function
int FuncCommand::dummyExecute(vector<string> strings, int index) {
    unsigned int i;
    int open = 0;
    for (i = index; i < strings.size(); i++) {
        if(strings[i] == "{") {
            open++;
        }
        if(strings[i] == "}") {
            open--;
            if(open == 0) {
                break;
            }
        }
    }
    return i + 1;
}

// save the function in functions map
int FuncCommand::execute(vector<string> strings, int index) {
    vector<string> subVector;
    DataManager* manager = DataManager::getInstance();
    int open = 0;
    unsigned int i;
    for (i = index; i < strings.size(); i++) {
        if(strings[i] == "{") {
            open++;
        }
        if(strings[i] == "}") {
            open--;
            //end of body
            if(open == 0) {
                break;
            }
        }
        if(i != (unsigned) index) {
            subVector.emplace_back(strings[i]);
        }
    }
    manager->addFunc(subVector, strings[index - 2], strings[index - 1]);
    return i + 1;
}

Func::Func(vector<string> inputCommands, string inputVar) {
    this->commands = inputCommands;
    this->var = inputVar;
}

//operate the function according the given parameter
void Func::operate(string valueToReplace) {
    Parser parser;
    vector<string> newVector = updatedVector(valueToReplace);
    parser.parse(newVector);
}

//replace the unknown var in the given parameter
vector<string> Func::updatedVector(string newValue) {
    vector<string> result = this->commands;
    string temp = "";
    int first;
    bool clear;
    for (unsigned int i = 0; i < result.size(); i++) {
        for (unsigned int j = 0; j < result[i].size(); j++) {
            clear = true;
            temp += result[i][j];
            // check if temp is prefix of var
            if(this->var.find(temp) == 0) {
                if(this->var == temp) {
                    //check if the found expression is match properly the unknown var
                    if((result[i].length() - 1 == j) || !(isalpha(result[i][j + 1]) || isdigit(result[i][j + 1]) || result[i][j + 1] == '_')) {
                        first = j - temp.length() + 1;
                        if ((first == 0) || !(isalpha(result[i][first - 1]) || isdigit(result[i][first - 1]) || result[i][first - 1] == '_')) {
                            result[i].replace(first, this->var.length(), newValue);
                            j -= this->var.length() - newValue.length();
                        }
                    }
                } else {
                    clear = false;
                }
            }
            if(clear) {
                temp = "";
            }
        }
    }
    return result;
}