#pragma once

#ifndef OUTPUT_H
#define OUTPUT_H

#include "Wire.h"
#include <string>

using namespace std;

class Output {
public:
	Output(string newName);
	void setValue(int newValue);
	int getValue() { return value; }

private:
	string name;
	int value;
};


#endif //OUTPUT_H