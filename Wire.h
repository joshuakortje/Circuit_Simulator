#pragma once

#ifndef WIRE_H
#define WIRE_h

#include <vector>
using namespace std;

class Gate;
const int HIGH = 1;
const int LOW = 0;
const int UNKNOWN = -1;

class Wire {
public:
	Wire(int newNumber);
	~Wire();
	int getValue();
	void updateWire( int newValue);
	void addGate(Gate* newGate);
private:
	int value;
	int number;
	vector<Gate *> nextGates;
};

#endif