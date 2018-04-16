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
	Wire* getWire();
	int readHistory();
	void addHistory(int newHistory);

private:
	string name;
	int value;
	Wire *inputWire;
	vector<int> history;
};

#endif //INPUT_H