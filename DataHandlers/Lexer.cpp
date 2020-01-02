
#include <iostream>
#include "Lexer.h"
#include <fstream>

/**
 * Lexer Class
 */
//get a file name and does lexing on the text of the file
vector<string> Lexer::doLexing(const string& fileName) {
    vector<string> strings;
    ifstream file;
    file.open(fileName);
    //if failed to open the file
    if (!file.is_open()) {
        file.close();
        exit(1);
    }
    string line;
    //run on all the lines in the text file, line by line
    while (getline(file, line)) {
        //removes spaces and tabs from the start and end of the line
        line = this->removeSpacesAndTabsFromEdges(line);
        //if this is a openDataServer command line
        string token = "openDataServer";
        int pos = line.find(token);
        if (pos == 0) {
            strings.emplace_back(token);
            line = line.substr(token.length() + 1, line.length() - token.length() - 2);
            line = this->removeSpaces(line);
            strings.emplace_back(line);
            continue;
        }
        //if this is a connectControlClient command line
        token = "connectControlClient";
        pos = line.find(token);
        if (pos == 0) {
            strings.emplace_back(token);
            line = line.substr(token.length() + 1, line.length() - token.length() - 2);
            line = this->removeSpaces(line);
            vector<string> ipAndPort = this->split(line, ",");
            strings.emplace_back(ipAndPort[0].substr(1, ipAndPort[0].length() - 2));
            strings.emplace_back(ipAndPort[1]);
            continue;
        }
        //if this is a var command line
        token = "var";
        pos = line.find(token);
        if (pos == 0) {
            strings.emplace_back(token);
            line = line.substr(token.length() + 1, line.length() - token.length() - 1);
            //all the var direction options
            string varOperator1 = "->";
            string varOperator2 = "<-";
            string varOperator3 = "=";
            string varOperator;
            vector<string> varAndInput;
            string varName;
            string varInput;
            if ((unsigned) line.find(varOperator1) != (unsigned) string::npos) {
                varOperator = varOperator1;
            } else if ((unsigned) line.find(varOperator2) != (unsigned) string::npos) {
                varOperator = varOperator2;
            } else {
                varOperator = varOperator3;
            }
            varAndInput = this->split(line, varOperator);
            varName = this->removeSpaces(varAndInput[0]);
            strings.emplace_back(varName);
            strings.emplace_back(varOperator);
            varInput = this->removeSpaces(varAndInput[1]);
            //if the var has a sim
            token = "sim";
            pos = varInput.find(token);
            if (pos == 0) {
                strings.emplace_back(token);
                varInput = varInput.substr(token.length() + 2, varInput.length() - token.length() - 4);
            }
            strings.emplace_back(varInput);
            continue;
        }
        //if this is a Print command line
        token = "Print";
        pos = line.find(token);
        if (pos == 0) {
            strings.emplace_back(token);
            line = line.substr(token.length() + 1, line.length() - token.length() - 2);
            line = this->removeSpacesAndTabsFromEdges(line);
            if (line[0] != '"') {
                line = this->removeSpaces(line);
            }
            strings.emplace_back(line);
            continue;
        }
        //if this is a Sleep command line
        token = "Sleep";
        pos = line.find(token);
        if (pos == 0) {
            strings.emplace_back(token);
            line = line.substr(token.length() + 1, line.length() - token.length() - 2);
            strings.emplace_back(line);
            continue;
        }
        //if this is a while or a if command line
        string whileToken = "while";
        string ifToken = "if";
        pos = line.find(whileToken);
        if (pos == 0) {
            token = whileToken;
        }
        pos = line.find(ifToken);
        if (pos == 0) {
            token = ifToken;
        }
        pos = line.find(token);
        if (pos == 0) {
            strings.emplace_back(token);
            line = line.substr(token.length(), line.length() - token.length() - 1);
            // all the condition options
            string comparison1 = "<";
            string comparison2 = ">";
            string comparison3 = "<=";
            string comparison4 = ">=";
            string comparison5 = "==";
            string comparison6 = "!=";
            string comparison;
            vector<string> terms;
            // get the right comparison token
            if (((unsigned) line.find(comparison1) != (unsigned) string::npos) && ((unsigned) line.find(comparison3) == (unsigned) string::npos)) {
                comparison = comparison1;
            } else if (((unsigned) line.find(comparison2) != (unsigned) string::npos) && ((unsigned) line.find(comparison4) == (unsigned) string::npos)) {
                comparison = comparison2;
            } else if ((unsigned) line.find(comparison3) != (unsigned) string::npos) {
                comparison = comparison3;
            } else if ((unsigned) line.find(comparison4) != (unsigned) string::npos) {
                comparison = comparison4;
            } else if ((unsigned) line.find(comparison5) != (unsigned) string::npos) {
                comparison = comparison5;
            } else {
                comparison = comparison6;
            }
            terms = this->split(line, comparison);
            terms[0] = this->removeSpaces(terms[0]);
            terms[1] = this->removeSpaces(terms[1]);
            if (terms[0][0] == '(') {
                terms[0] = terms[0].substr(1, terms[0].size() - 1);
            }
            if (terms[1][terms[1].size() - 1] == ')') {
                terms[1] = terms[1].substr(0, terms[1].size() - 1);
            }
            strings.emplace_back(terms[0]);
            strings.emplace_back(comparison);
            strings.emplace_back(terms[1]);
            strings.emplace_back("{");
            continue;
        }
        //if this just a '}' line
        token = "}";
        pos = line.find(token);
        if (pos != -1) {
            strings.emplace_back(token);
            continue;
        }
        //if this is a set command line
        token = "=";
        pos = line.find(token);
        if (pos != -1) {
            vector<string> terms = this->split(line, token);
            strings.emplace_back(this->removeSpaces(terms[0]));
            strings.emplace_back(token);
            strings.emplace_back(this->removeSpaces(terms[1]));
            continue;
        }
        //if this is a function declaration command line
        token = "{";
        pos = line.find(token);
        if (pos != -1) {
            line = this->removeSpaces(line.substr(0, line.length() - 1));
            line = line.substr(0, line.length() - 1);
            vector<string> tokens = this->split(line, "(var");
            strings.emplace_back(tokens[0]);
            strings.emplace_back(tokens[1]);
            strings.emplace_back(token);
            continue;
        }
        //if this is a function call command line
        string token1 = "(";
        string token2 = ")";
        if (((unsigned) line.find(token1) != (unsigned) string::npos) && ((unsigned) line.find(token2) != (unsigned) string::npos)) {
            line = this->removeSpaces(line);
            line = line.substr(0, line.length() - 1);
            vector<string> tokens = this->split(line, "(");
            strings.emplace_back(tokens[0]);
            strings.emplace_back(tokens[1]);
            continue;
        }
    }
    //close the file and return the strings vector
    file.close();
    return strings;
}
//remove spaces from the given string
string Lexer::removeSpaces(const string& str) {
    string result;
    for (char c : str) {
        if (c != ' ') {
            string s(1, c);
            result += s;
        }
    }
    return result;
}
//remove spaces and tabs from the start of the given string
string Lexer::removeSpacesAndTabsFromStart(const string &str) {
    string result;
    bool startFlag = false;
    for (char c : str) {
        if ((c != ' ') && (c != '\t')) {
            startFlag = true;
        }
        if (startFlag) {
            string s(1, c);
            result += s;
        }
    }
    return result;
}
//remove spaces and tabs from the end of the given string
string Lexer::removeSpacesAndTabsFromEnd(const string &str) {
    string result;
    bool endFlag = true;
    for (int i = (int) str.length() - 1; i >= 0; i--) {
        if ((str[i] != ' ') && (str[i] != '\t')) {
            endFlag = false;
        }
        if (!endFlag) {
            string s(1, str[i]);
            result = s + result;
        }
    }
    return result;
}
//remove spaces and tabs from the start and end of the given string
string Lexer::removeSpacesAndTabsFromEdges(const string &str) {
    string result;
    result = this->removeSpacesAndTabsFromStart(str);
    result = this->removeSpacesAndTabsFromEnd(result);
    return result;
}
//split the given string by the given delimiter
vector<string> Lexer::split(string str, const string& delimiter) {
    vector<string> strings;
    string token;
    int pos = str.find(delimiter);
    while ((unsigned) pos != (unsigned) string::npos) {
        token = str.substr(0, pos);
        strings.emplace_back(token);
        str.erase(0, pos + delimiter.length());
        pos = str.find(delimiter);
    }
    strings.emplace_back(str);
    return strings;
}