
#include "SleepCommand.h"
#include <chrono>
#include <thread>

//sleep this thread for given time
int SleepCommand::execute(vector<string> strings, int index) {
    DataManager *m = DataManager::getInstance();
    // convert strings[index + 1] to number
    Expression* exp = m->getInter()->interpret(strings[index + 1]);
    double time = exp->calculate();
    delete exp;
    this_thread::sleep_for(chrono::milliseconds((int)time));
    return index + 2;
}

//skip the sleeping
int SleepCommand::dummyExecute(vector<string> strings, int index) {
    if (strings.empty()) {
        cerr << "There are no strings"<<endl;
    }
    // increase returned index by 2 (sleep + 1 for time)
    return index + 2;
}
