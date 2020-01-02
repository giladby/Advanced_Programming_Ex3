
#include <string>
#include <vector>
#include "DataHandlers/Lexer.h"
#include "DataHandlers/DataManager.h"
#include "DataHandlers/Parser.h"

using namespace std;

int main(int argc, char** argv) {
    // make a data manager object, a parser and a lexer
    DataManager* manager = DataManager::getInstance();
    Parser* parser = new Parser();
    Lexer* lexer = new Lexer();
    string fileName;
    // if there's an argument
    if (argc >= 2) {
        // this argument is the file name
        fileName = argv[1];
    } else {
        cerr << "no arguments was found" << endl;
        exit(1);
    }
    // lex the file lines
    vector<string> strings = lexer->doLexing(fileName);
    // parse the commands
    parser->parse(strings);
    // set the done flag to true after the parsing is complete
    manager->setDone();
    // delete all the allocated memory
    delete lexer;
    delete parser;
    delete manager;
    return 0;
}
