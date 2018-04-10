#pragma once
#include <iostream>
#include <string>
#include "Wire.h"


class Input {
public:
	Input(std::string newName, Wire *newInputWire);

	std::string getName() { return name; }

	void setValue(int newValue);
private:
	std::string name;
	int value;
};