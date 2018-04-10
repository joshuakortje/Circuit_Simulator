#pragma once

#ifndef OUTPUT_H
#define OUTPUT_H

#include "Wire.h"

class Output {
public:
	Output(string newName, Wire *newInputWire);
	void updateOutput(int newValue);
	int getOutput();

private:
	string name;
	int value;
};


#endif //OUTPUT_H