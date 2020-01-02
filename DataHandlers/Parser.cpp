
#include "Parser.h"
#include "DataManager.h"

//parsing the given orders
void Parser::parse(vector<string> stringsVector) {
    DataManager* manager = DataManager::getInstance();
    unordered_map<string,Command*>* commandsMap = manager->getCommandsMap();
    unsigned int index = 0;
    Command* c;
    while(index < stringsVector.size()) {
        if(commandsMap->find(stringsVector[index]) != commandsMap->end()) {
            c = (*commandsMap)[stringsVector[index]];
            index = c->execute(stringsVector, index);
        } else {
            if(manager->isFunc(stringsVector[index])) {
                (*manager->getFuncMap())[stringsVector[index]]->operate(stringsVector[index + 1]);
                index++;
            }
            index++;
        }
    }
}
