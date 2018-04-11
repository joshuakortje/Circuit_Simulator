#pragma once

#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>
#include "Wire.h"

using namespace std;

class Input {
public:
	Input(string newName, Wire *newInputWire);
	string getName() { return name; }
	void setValue(int newValue);

private:
	string name;
	int value;
	Wire *inputWire;
	vector<int> history;
};

#endif //INPUT_H