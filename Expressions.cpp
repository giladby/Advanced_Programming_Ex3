//
// Created by giladby on 12/12/2019.
//

#include "Expressions.h"
#include <iostream>
#include <bits/stdc++.h>
#include <ctype.h>
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <queue>

using namespace std;

// Variable class methods

double Variable::calculate() {
    return this->value;
}

Variable::Variable(string inputName, double inputVal) {
    this->value = inputVal;
    this->name = inputName;
}
Variable& Variable::operator+=(double val) {
    this->value += val;
    return *this;
}

Variable& Variable::operator-=(double val) {
    this->value -= val;
    return *this;
}

Variable& Variable::operator--() {
    this->value --;
    return *this;
}

Variable& Variable::operator--(int) {
    this->value --;
    return *this;
}

Variable& Variable::operator++(int) {
    this->value ++;
    return *this;
}

Variable& Variable::operator++() {
    this->value ++;
    return *this;
}

// Value class methods

double Value::calculate() {
    return this->value;
}

Value::Value(double val) : value(val) {}

// BinaryOperator class methods

BinaryOperator::BinaryOperator(Expression *inputLeft, Expression *inputRight) {
    this->left = inputLeft;
    this->right = inputRight;
}

BinaryOperator::~BinaryOperator() {
    if(this->right != nullptr) {
        delete this->right;
    }
    if(this->left != nullptr) {
        delete this->left;
    }
}

// UnaryOperator class methods

UnaryOperator::UnaryOperator(Expression *inputExp) {
    this->exp = inputExp;
}

UnaryOperator::~UnaryOperator() {
    if(this->exp != nullptr) {
        delete this->exp;
    }
}

// Plus class methods

Plus::Plus(Expression *inputLeft, Expression *inputRight) : BinaryOperator(inputLeft, inputRight) {}

double Plus::calculate() {
    return this->left->calculate() + this->right->calculate();
}

// Minus class methods

Minus::Minus(Expression *inputLeft, Expression *inputRight) : BinaryOperator(inputLeft, inputRight) {}

double Minus::calculate() {
    return this->left->calculate() - this->right->calculate();
}

// Div class methods

Div::Div(Expression *inputLeft, Expression *inputRight) : BinaryOperator(inputLeft, inputRight) {}

double Div::calculate() {
    if(this->right->calculate() == 0) {
        throw "bad input";
    }
    return this->left->calculate() / this->right->calculate();
}

// Mul class methods

Mul::Mul(Expression *inputLeft, Expression *inputRight) : BinaryOperator(inputLeft, inputRight) {}

double Mul::calculate() {
    return this->left->calculate() * this->right->calculate();
}

// UPlus class methods

UPlus::UPlus(Expression *inputExp) : UnaryOperator(inputExp) {}
double UPlus::calculate() {
    return this->exp->calculate();
}

// Mul class methods

UMinus::UMinus(Expression *inputExp) : UnaryOperator(inputExp) {}
double UMinus::calculate() {
    //avoid '-0' problem
    if(this->exp->calculate() == 0) {
        return this->exp->calculate();
    }
    return this->exp->calculate() * (-1);
}

// Interpreter class methods

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

void Interpreter::setVariables(string str) {
    insertToMap(str);
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
        if(!isdigit(c) && c != '.') {
            return false;
        }
        if(i == 0) {
            //numbers have to begin with a digit
            if(isalpha(c)) {
                return false;
            }
        } else {
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

bool Interpreter::properNumberMap(string str) {
    int length = str.length();
    if(length > 0 && str[0] == '-') {
        return this->properNumber(str.substr(1,length-1));
    }
    return this->properNumber(str);
}

void Interpreter::insertToMap(string str) {
    //spilt the string by ';'.
    vector<string> v1 = this->split (str, ';');
    double number;
    if(str == "") {
        throw "bad input";
    }
    for (auto v : v1) {
        //there is '=' char in substring
        if(v.find('=') != string::npos) {
            // split the string by '='.
            vector<string> v2 = this->split (v, '=');
            // check that the left side is proper variable and the right side is proper number
            if(v2.size() == 2 && this->properVariable(v2[0]) && this->properNumberMap(v2[1])) {
                //convert the number string to double
                number = strtod(v2[1].c_str(), NULL);
                this->varMap[v2[0]] = number;
            } else {
                throw "bad input";
            }
        } else {
            throw "bad input";
        }
    }
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
                    if(this->varMap.count(str) == 0)
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
            if(this->varMap.count(str) == 0)
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

//check if the string contains any variable from the 'from' index
bool Interpreter::followVariable(string str, int from) {
    string var = "";
    char c;
    int length = str.length();
    for (int i = from; i < length ; i++) {
        c = str[i];
        if(c != '_' && !isdigit(c) && !isalpha(c)) {
            break;
        }
        var += c;
    }
    return !this->properNumber(var) && this->properVariable(var);
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
                            if(this->followVariable(input, i + 1)) {
                                throw "bad input";
                            }
                            //new signs for unary operators
                            if(c == '+') {
                                c = '^';
                            }
                            if(c == '-') {
                                c = '~';
                            }
                        }
                    }
                    while ((!operators.empty()) && (this->isOperator(operators.top()) || this->isUnaryOperator(operators.top())) &&
                           this->getPrecedence(c) < this->getPrecedence(operators.top())) {
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
                exps.push(new Value(strtod(str.c_str(), NULL)));
            } else {
                if(this->properVariable(str)) {
                    if(this->varMap.find(str)->second < 0) {
                        exps.push(new UMinus(new Variable(str, this->varMap.find(str)->second * -1)));
                    } else {
                        exps.push(new Variable(str, this->varMap.find(str)->second));
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

//spilt sting by char
vector<string> Interpreter::split(const string &str, char sign) {
    vector<string> result;
    stringstream ss (str);
    string item;

    while (getline (ss, item, sign)) {
        result.push_back (item);
    }

    return result;
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
