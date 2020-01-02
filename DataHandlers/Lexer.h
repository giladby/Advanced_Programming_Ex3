
#ifndef EX3_NEW_LEXER_H
#define EX3_NEW_LEXER_H

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
    string removeSpacesAndTabsFromStart(const string& str);
    string removeSpacesAndTabsFromEnd(const string& str);
    string removeSpacesAndTabsFromEdges(const string& str);
    vector<string> split(string str, const string& delimiter);
};


#endif //EX3_NEW_LEXER_H
