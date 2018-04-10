#pragma once

//#ifndef OUTPUT_H
//#define OUTPUT_H

#include "Wire.h"
#include <string>

class Output {
public:
	Output(std::string newName, Wire *newInputWire);
	void setValue(int newValue);
	int getValue() { return value; }

private:
	std::string name;
	int value;
};


//#endif //OUTPUT_H