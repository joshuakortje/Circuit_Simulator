#include <iostream>
#include <string>
#include "stdafx.h"
#include "Output.h"

Output::Output(string newName) : name(newName) {
	value = UNKNOWN;
}

void Output::setValue(int newValue) {
	value = newValue;
}

