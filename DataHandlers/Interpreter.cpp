
#include "Interpreter.h"
#include "Expressions/Minus.h"
#include "Expressions/Plus.h"
#include "Expressions/Div.h"
#include "Expressions/Mul.h"
#include "Expressions/UMinus.h"
#include "Expressions/UPlus.h"
#include <stack>

// Interpreter class methods

void Interpreter::setMap(unordered_map<string, Var *> * inputVarsMap) {
    this->varsMap = inputVarsMap;
}

bool Interpreter::isParenthesisOk(string input) {
    int counter = 0;
    int open = 0;
    int length = input.length();
    for(int i = 0; i < length; i++) {
        if(input[i] == '(') {
            // open parenthesis can't appear after close parenthesis
            if(i > 0 && input[i - 1] == ')') {
                return false;
            }
            counter++;
            open = i;
        }
        if(input[i] == ')') {
            if(counter == 0 || open == (i - 1)) {
                // close parenthesis can't appear before open parenthesis.
                return false;
            }
            counter--;
        }
    }
    // the amount of close and open parenthesis has to be equal.
    return (counter == 0);
}

bool Interpreter::properVariable(string str) {
    char c;
    int length = str.length();
    for(int i = 0; i < length; i++) {
        c = str[i];
        if(i == 0) {
            // variable's name has to begin with a letter
            if(isdigit(c)) {
                return false;
            }
        }
        if(!isalpha(c) && !isdigit(c) && c != '_') {
            return false;
        }
    }
    // variable's name can't be empty
    return length > 0;
}

bool Interpreter::properNumber(string str) {
    char c;
    int point = 0;
    int length = str.length();
    for(int i = 0; i < length; i++) {
        c = str[i];
        if(!(isdigit(c) || c == '.' || c == '-')) {
            return false;
        }
        if(i == 0) {
            //numbers have to begin with a digit
            if(!(isdigit(c) || c == '-')) {
                return false;
            }
        } else {
            if(c == '-') {
                return false;
            }
            if(c == '.') {
                // numbers have only one point.
                if(point == 1) {
                    return false;
                }
                point++;
            }
        }
    }
    return length > 0;
}

// check that every variable in the string is contained in the variables map.
bool Interpreter::isVariableHasValue(string input) {
    string str = "";
    int length = input.length();
    for(int i = 0; i < length; i++) {
        if(input[i] != '(' && input[i] != ')' && input[i] != '.' && !this->isOperator(input[i])) {
            str += input[i];
        } else {
            if(str != "") {
                //check that the variable is proper
                if(!this->properNumber(str)) {
                    //check if the variable exist in the map
                    if((*this->varsMap).find(str) == (*this->varsMap).end())
                    {
                        return false;
                    }
                }
                str = "";
            }
        }
    }
    // taking care for variable in the end of string
    if(str != "") {
        if(!this->properNumber(str)) {
            if((*this->varsMap).find(str) == (*this->varsMap).end())
            {
                return false;
            }
        }
    }
    return true;
}

int Interpreter::getPrecedence(char c) {
    switch (c) {
        case '+':
            return 0;
        case '-':
            return 0;
        case '/':
            return 1;
        case '*':
            return 1;
        case '^':
            return 1;
        case '~':
            return 1;
            //error
        default:
            return -1;
    }
}

//this is the first part of the shutting yard algorithm - convert the string to postfix queue
queue<string> Interpreter::toQueue(string input) {
    stack <char> operators;
    char c;
    bool open = false;
    string str = "";
    queue <string> numbersQueue;
    bool gettingNumber = false;
    int length = input.length();
    for(int i = 0; i < length; i++) {
        c = input[i];
        if(c == '(') {
            // variable/number can't be before open parenthesis
            if(gettingNumber) {
                throw "bad input";
            }
            open = true;
            operators.push(c);
        } else {
            if(c == ')') {
                // close parenthesis can be in end of string, before another close parenthesis, or before an operator
                if(!(i == (length - 1) || this->isOperator(input[i + 1]) || input[i + 1] == ')')) {
                    throw "bad input";
                }
                if(gettingNumber) {
                    gettingNumber = false;
                    //check that the variable/number is proper
                    if(!this->properNumber(str) && !this->properVariable(str)) {
                        throw "bad input";
                    }
                    numbersQueue.push(str);
                    str = "";
                }
                while(operators.top() != '(') {
                    numbersQueue.push(string(1,operators.top()));
                    operators.pop();
                }
                operators.pop();
                open = false;
            } else {
                if(this->isOperator(c)) {
                    if(gettingNumber) {
                        gettingNumber = false;
                        //check that the variable/number is proper
                        if(!this->properNumber(str) && !this->properVariable(str)) {
                            throw "bad input";
                        }
                        numbersQueue.push(str);
                        str = "";
                    }
                    //operators can't be in end of sting or after another operator
                    if(i == (length - 1) || input[i + 1] == ')' || (i > 0 && this->isOperator(input[i - 1]))) {
                        throw "bad input";
                    }
                    if(c == '*' || c == '/') {
                        // '*' and '/' can't be in begin of string
                        if(open || i == 0) {
                            throw "bad input";
                        }
                        // '-'/'+' situation
                    } else {
                        // '-' and '+' in in begin of string or after open parenthesis are unary operators
                        if(i == 0 || open) {
                            if(c == '+') {
                                c = '^';
                            }
                            if(c == '-') {
                                c = '~';
                            }
                        }
                    }
                    while ((!operators.empty()) && (this->isOperator(operators.top()) || this->isUnaryOperator(operators.top())) &&
                           this->getPrecedence(c) <= this->getPrecedence(operators.top())) {
                        numbersQueue.push(string(1,operators.top()));
                        operators.pop();
                    }
                    operators.push(c);
                    open = false;
                } else {
                    if(!gettingNumber) {
                        gettingNumber = true;
                    }
                    str += c;
                    open = false;
                }
            }
        }
    }
    //taking care variable/number in end of string
    if(gettingNumber) {
        if(!this->properNumber(str) && !this->properVariable(str)) {
            throw "bad input";
        }
        numbersQueue.push(str);
    }
    while(!operators.empty()) {
        numbersQueue.push(string(1, operators.top()));
        operators.pop();
    }
    return numbersQueue;
}

Expression* Interpreter::makeAnExpression(string input) {
    stack <Expression*> exps;
    //convert the string to postfix queue
    queue<string> shuntingYard = this->toQueue(input);
    string str;
    Expression* exp1;
    Expression* exp2;
    int length;
    while(!shuntingYard.empty()) {
        str = shuntingYard.front();
        shuntingYard.pop();
        length = str.length();
        if(length == 1 && (this->isOperator(str[0]) || this->isUnaryOperator(str[0]))) {
            exp1 = exps.top();
            exps.pop();
            switch (str[0]) {
                case '+':
                    exp2 = exps.top();
                    exps.pop();
                    exps.push(new Plus(exp2, exp1));
                    break;
                case '-':
                    exp2 = exps.top();
                    exps.pop();
                    exps.push(new Minus(exp2, exp1));
                    break;
                case '/':
                    exp2 = exps.top();
                    exps.pop();
                    exps.push(new Div(exp2, exp1));
                    break;
                case '*':
                    exp2 = exps.top();
                    exps.pop();
                    exps.push(new Mul(exp2, exp1));
                    break;
                case '^':
                    exps.push(new UPlus(exp1));
                    break;
                case '~':
                    exps.push(new UMinus(exp1));
                    break;
            }
        } else {
            if(this->properNumber(str)) {
                exps.push(new Var(strtod(str.c_str(), NULL), false));
            } else {
                if(this->properVariable(str)) {
                    if((*this->varsMap).find(str) != (*this->varsMap).end()) {
                        exps.push((*this->varsMap)[str]);
                    }
                }
            }
        }
    }
    return exps.top();
}



bool Interpreter::isOperator(char c) {
    return (c == '-' || c == '*' || c == '/' || c == '+');
}

bool Interpreter::isUnaryOperator(char c) {
    return (c == '~' || c == '^' );
}

bool Interpreter::isSyntaxOk(string input) {
    char c;
    int length = input.length();
    for(int i = 0; i < length; i++) {
        c = input[i];
        // '.' has to be between two numbers
        if(c == '.') {
            if(!(i > 0 && i < length) || !(isdigit(input[i-1]) && isdigit(input[i + 1]))) {
                return false;
            }
        }
        if(!this->isOperator(c) && !isdigit(c) && !isalpha(c) && c != '.' && c != '_' && c != ')' && c != '(') {
            return false;
        }
    }
    return true;
}

Expression* Interpreter::interpret(string str) {
    if(!this->isSyntaxOk(str)) {
        throw "bad input";
    }
    if(!this->isParenthesisOk(str)) {
        throw "bad input";
    }
    if(!this->isVariableHasValue(str)) {
        throw "bad input";
    }
    return this->makeAnExpression(str);
}
