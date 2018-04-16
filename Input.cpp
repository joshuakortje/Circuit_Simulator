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

//returns the wire 
Wire* Input::getWire() {
	return inputWire;
}

// return the first element in the vector and erase it
int Input::readHistory() {
	if (history.size() == 0) return EMPTY_HISTORY;
	else {
		int temp = history.front();
		history.erase(history.begin());
		return temp;
	}
}

//add new history to the back of the vector
void Input::addHistory(int newHistory) {
	history.push_back(newHistory);
}