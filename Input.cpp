#include <iostream>
#include <string>
#include "stdafx.h"
#include "Input.h"

using namespace std;

Input::Input(string newName, Wire *newInputWire) : name(newName) {
	newInputWire = nullptr;
}

void Input::setValue(int newValue) {
	value = newValue;
}