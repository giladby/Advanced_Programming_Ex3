
#include "Parser.h"
#include "DataManager.h"

//parsing the given commands
void Parser::parse(vector<string> stringsVector) {
    DataManager* manager = DataManager::getInstance();
    // get the commands map
    unordered_map<string,Command*>* commandsMap = manager->getCommandsMap();
    unsigned int index = 0;
    Command* c;
    // while there are still commands to be executed
    while(index < stringsVector.size()) {
        // if this is a command that is in the map
        if(commandsMap->find(stringsVector[index]) != commandsMap->end()) {
            c = (*commandsMap)[stringsVector[index]];
            // execute this command
            index = c->execute(stringsVector, index);
        } else {
            // if this is a function command
            if(manager->isFunc(stringsVector[index])) {
                (*manager->getFuncMap())[stringsVector[index]]->operate(stringsVector[index + 1]);
                index++;
            }
            index++;
        }
    }
}
