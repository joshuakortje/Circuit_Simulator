#pragma once

#ifndef GATE_H
#define GATE_H

#include <string>
#include <vector>

using namespace std;

class Wire;

class Gate {
public:
	Gate(string newType, int newDelay, Wire *newInput1, Wire *newInput2, Wire *newOutput);
	string getType();
	void updateGate();
	bool checkOutputChange();
	int runGateLogic(); // it did have Wire *newInput, int input as parameters
	int getCurrentOutput(); 
private:
	string type;
	int delay;
	Wire *input1;
	Wire *input2;
	Wire *output;
};
#endif