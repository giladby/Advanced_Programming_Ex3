
#ifndef AP_EX3_LEXER_H
#define AP_EX3_LEXER_H

#include <string>
#include <vector>
using namespace std;


/**
 * Lexer Class
 */
class Lexer {
public:
    vector<string> doLexing(const string& fileName);
    string removeSpaces(const string& str);
    string removeTabs(const string& str);
    vector<string> split(string str, const string& delimiter);
};


#endif //AP_EX3_LEXER_H
