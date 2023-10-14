#ifndef TESTER_H
#define TESTER_H

#include <iostream>
#include "Timer.h"
#include <fstream>

class Tester
{
public:
    Tester(int numOfTests);               // constructor
    void testAlgorithm(std::string type); // method for testing algorithm

private:
    int numOfTests;
};

#endif
