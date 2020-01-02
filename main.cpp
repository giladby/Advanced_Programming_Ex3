
#include <string>
#include <vector>
#include "DataHandlers/Lexer.h"
#include "DataHandlers/DataManager.h"
#include "DataHandlers/Parser.h"

using namespace std;

int main(int argc, char** argv) {
    DataManager* manager = DataManager::getInstance();
    Parser* parser = new Parser();
    Lexer* lexer = new Lexer();
    string fileName;
    if (argc >= 2) {
        fileName = argv[1];
    } else {
        cerr << "no arguments was found" << endl;
        exit(1);
    }
    vector<string> strings = lexer->doLexing(fileName);
    parser->parse(strings);
    manager->setDone();
    delete lexer;
    delete parser;
    delete manager;
    return 0;
}
