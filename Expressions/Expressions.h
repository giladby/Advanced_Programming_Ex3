
#ifndef EX3_NEW_EXPRESSIONS_H
#define EX3_NEW_EXPRESSIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
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

#endif //EX3_NEW_EXPRESSIONS_H
