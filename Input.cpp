#include <iostream>
#include <string>
#include "stdafx.h"
#include "Input.h"

using namespace std;

Input::Input(string newName, int newValue) : name(newName), value(newValue) {
}

void Input::setValue(int newValue) {
	value = newValue;
}