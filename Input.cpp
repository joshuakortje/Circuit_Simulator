#include <iostream>
#include <string>
#include "stdafx.h"
#include "Input.h"

Input::Input(string newName, Wire *newInputWire) : name(newName) {
	inputWire = newInputWire;
}

void Input::setValue(int newValue) {
	value = newValue;
}