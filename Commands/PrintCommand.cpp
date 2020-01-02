#include "PrintCommand.h"

//print the asked data/the given string
int PrintCommand::execute(vector<string> strings, int index) {
    string printedStr;
    DataManager *m = DataManager::getInstance();
    double value;
    //check if the current printing is a string or data
    if(strings[index + 1][0] == '"') {
        printedStr = strings[index + 1];
        // remove the first ' " ' and the length of the sub string is
        // the whole string's size - the first ' " ' - the second ' " ' = the string's size - 2
        printedStr = printedStr.substr(1, printedStr.length() - 2);
        cout << printedStr << "\n";
    } else {
        Expression* exp = m->getInter()->interpret(strings[index + 1]);
        value = exp->calculate();
        if (dynamic_cast<Var*>(exp) != nullptr) {
            if (!dynamic_cast<Var*>(exp)->hasName()) {
                delete exp;
            }
        } else {
            delete exp;
        }
        cout << value << "\n";
    }
    // increase returned index by 2 (printed + 1 for next)
    return index + 2;
}

//skip the printing
int PrintCommand::dummyExecute(vector<string> strings, int index) {
    if (strings.empty()) {
        cerr << "There are no strings"<<endl;
    }
    // increase returned index by 2 (printed + 1 for next)
    return index + 2;
}