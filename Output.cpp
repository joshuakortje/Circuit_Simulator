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

//This function pushs new History to the back of the vector
void Output::addHistory(int newHistory) {
	history.push_back(newHistory);
}

//return the front of the vector and remove it
int Output::readHistory() {
	if (history.size() == 0) return EMPTY_HISTORY;
	else {
		int temp = history.front();
		history.erase(history.begin());
		return temp;
	}
}