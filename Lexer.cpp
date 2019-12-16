
#include <iostream>
#include "Lexer.h"
#include <fstream>
using namespace std;

/**
 * Lexer Class
 */
vector<string> Lexer::doLexing(const string& fileName) {
    vector<string> strings;
    ifstream file;
    file.open(fileName);
    if (!file.is_open()) {
        file.close();
        exit(1);
    }
    string line;
    while (getline(file, line)) {
        line = this->removeTabs(line);
        string token = "openDataServer";
        int pos = line.find(token);
        if (pos == 0) {
            strings.emplace_back(token);
            line = line.substr(token.length() + 1, line.length() - token.length() - 2);
            line = this->removeSpaces(line);
            strings.emplace_back(line);
            continue;
        }
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
        token = "var";
        pos = line.find(token);
        if (pos == 0) {
            strings.emplace_back(token);
            line = line.substr(token.length() + 1, line.length() - token.length() - 1);
            string varOperator1 = "->";
            string varOperator2 = "<-";
            string varOperator3 = "=";
            string varOperator;
            vector<string> varAndInput;
            string varName;
            string varInput;
            if (line.find(varOperator1) != -1) {
                varOperator = varOperator1;
            } else if (line.find(varOperator2) != -1) {
                varOperator = varOperator2;
            } else {
                varOperator = varOperator3;
            }
            varAndInput = this->split(line, varOperator);
            varName = this->removeSpaces(varAndInput[0]);
            strings.emplace_back(varName);
            strings.emplace_back(varOperator);
            varInput = this->removeSpaces(varAndInput[1]);
            token = "sim";
            pos = varInput.find(token);
            if (pos == 0) {
                strings.emplace_back(token);
                varInput = varInput.substr(token.length() + 2, varInput.length() - token.length() - 4);
            }
            strings.emplace_back(varInput);
            continue;
        }
        token = "Print";
        pos = line.find(token);
        if (pos == 0) {
            strings.emplace_back(token);
            line = line.substr(token.length() + 1, line.length() - token.length() - 2);
            strings.emplace_back(line);
            continue;
        }
        token = "Sleep";
        pos = line.find(token);
        if (pos == 0) {
            strings.emplace_back(token);
            line = line.substr(token.length() + 1, line.length() - token.length() - 2);
            strings.emplace_back(line);
            continue;
        }
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
            string comparison1 = "<";
            string comparison2 = ">";
            string comparison3 = "<=";
            string comparison4 = ">=";
            string comparison5 = "==";
            string comparison6 = "!=";
            string comparison;
            vector<string> terms;
            if ((line.find(comparison1) != -1) && (line.find(comparison3) == -1)) {
                comparison = comparison1;
            } else if ((line.find(comparison2) != -1) && (line.find(comparison4) == -1)) {
                comparison = comparison2;
            } else if (line.find(comparison3) != -1) {
                comparison = comparison3;
            } else if (line.find(comparison4) != -1) {
                comparison = comparison4;
            } else if (line.find(comparison5) != -1) {
                comparison = comparison5;
            } else {
                comparison = comparison6;
            }
            terms = this->split(line, comparison);
            strings.emplace_back(this->removeSpaces(terms[0]));
            strings.emplace_back(comparison);
            strings.emplace_back(this->removeSpaces(terms[1]));
            strings.emplace_back("{");
            continue;
        }
        token = "}";
        pos = line.find(token);
        if (pos != -1) {
            strings.emplace_back(token);
            continue;
        }
        token = "=";
        pos = line.find(token);
        if (pos != -1) {
            vector<string> terms = this->split(line, token);
            strings.emplace_back(this->removeSpaces(terms[0]));
            strings.emplace_back(token);
            strings.emplace_back(this->removeSpaces(terms[1]));
            continue;
        }
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
        string token1 = "(";
        string token2 = ")";
        if ((line.find(token1) != -1) && (line.find(token2) != -1)) {
            line = this->removeSpaces(line);
            line = line.substr(0, line.length() - 1);
            vector<string> tokens = this->split(line, "(");
            strings.emplace_back(tokens[0]);
            strings.emplace_back(tokens[1]);
            continue;
        }
    }


    file.close();
    return strings;
}
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
string Lexer::removeTabs(const string& str) {
    string result;
    for (char c : str) {
        if (c != '\t') {
            string s(1, c);
            result += s;
        }
    }
    return result;
}
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