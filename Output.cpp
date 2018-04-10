#include <iostream>
#include <string>
#include "stdafx.h"
#include "Output.h"


using namespace std;

Output::Output(std::string newName, Wire *newInputWire) : name(newName) {
	newInputWire = nullptr;
}

void Output::setValue(int newValue) {
	value = newValue;
}

