//
// Created by giladby on 12/12/2019.
//

#ifndef EX3_EXPRESSIONS_H
#define EX3_EXPRESSIONS_H

#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <queue>

using namespace std;

/**
* Expression Interface
*/
class Expression {

public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

/**
 * Value class
 */
class Value : public Expression{
private:
    const double value;

public:
    Value(double val);
    double calculate();
};

/**
 * Variable class
 */
class Variable : public Expression {
private:
    string name;
    double value;
public:
    Variable(string name, double val);
    double calculate();
    Variable& operator+=(double val);
    Variable& operator-=(double val);
    Variable& operator--();
    Variable& operator++();
    Variable& operator--(int);
    Variable& operator++(int);
};

/**
 * Variable class
 */
class UnaryOperator : public Expression {
protected:
    Expression* exp;
public:
    UnaryOperator(Expression* exp);
    ~UnaryOperator();
};

/**
 * BinaryOperator class
 */
class BinaryOperator : public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    BinaryOperator(Expression* left, Expression* right);
    ~BinaryOperator();
};

/**
 * Plus class
 */
class Plus : public BinaryOperator {
public:
    Plus(Expression* left, Expression* right);
    double calculate();
};

/**
 * Minus class
 */
class Minus : public BinaryOperator {
public:
    Minus(Expression* left, Expression* right);
    double calculate();
};

/**
 * Multiply class
 */
class Mul : public BinaryOperator {
public:
    Mul(Expression* left, Expression* right);
    double calculate();
};

/**
 * Division class
 */
class Div : public BinaryOperator {
public:
    Div(Expression* left, Expression* right);
    double calculate();
};

/**
 * UPlus class
 */
class UPlus : public UnaryOperator {
public:
    UPlus(Expression* exp);
    double calculate();
};

/**
 * UMinus class
 */
class UMinus : public UnaryOperator {
public:
    UMinus(Expression* exp);
    double calculate();
};

/**
 * Interpreter class
 */
class Interpreter {
private:
    map<string, double> varMap;
    int getPrecedence(char c);
    bool followVariable(string str, int from);
    bool isParenthesisOk(string str);
    bool isVariableHasValue(string str);
    bool isSyntaxOk(string str);
    bool isOperator(char c);
    bool properVariable(string str);
    bool properNumber(string str);
    bool properNumberMap(string str);
    bool isUnaryOperator(char c);
    void insertToMap(string str);
    queue<string> toQueue(string str);
    vector<string> split (const string &s, char delim);
    Expression* makeAnExpression(string str);

public:
    Expression* interpret(string str);
    void setVariables(string str);
};

#endif //EX3_EXPRESSIONS_H
