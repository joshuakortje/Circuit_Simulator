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
	~Gate();
	string getType();
	void updateGate();
	bool checkOutputChange();
	int runGateLogic();
	int getCurrentOutput();
private:
	string type;
	int delay;
	Wire *input1;
	Wire *input2;
	Wire *output;
};
#endif