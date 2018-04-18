#pragma once

#ifndef WIRE_H
#define WIRE_h

#include <vector>
#include <string>
using namespace std;

class Gate;
const int HIGH = 1;
const int LOW = 0;
const int UNKNOWN = -1;
const int EMPTY_HISTORY = -2;

class Wire {
public:
	Wire(int newNumber, string name, bool InOut);
	int getValue();
	bool getInOut();
	int getNumber() const { return number; }
	string getName() const { return name; }
	void updateWire( int newValue);
	void addGate(Gate* newGate);
	vector<Gate *> getNextGates();
	void addHistory(int newHistory);
	int readHistory();

private:
	bool isInOut; //true for inputs and outputs
	int value;
	int number;
	string name;
	vector<Gate *> nextGates;
	vector<int> history;
};

#endif