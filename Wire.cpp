#include "stdafx.h"
#include "Wire.h"
#include "Gate.h"

// Constructor
Wire::Wire(int newNumber, string name, bool InOut) : number(newNumber), name(name), isInOut(InOut) {
	// intitialize the data members
	// there are currently no nextGates so we leave the vector empty
	value = UNKNOWN;
}

// Changes the Wire value
void Wire::updateWire(int newValue){
	//give the Wire the updated value
	value = newValue;
}

//return the front of the vector and remove it
int Wire::readHistory() {
	if (history.size() == 0) {
		return EMPTY_HISTORY;
	}
	else {
		int temp = history.front();
		history.erase(history.begin());
		return temp;
	}
}


// Adder Implementations

// Adds a gate to the end of the Wire
void Wire::addGate(Gate * newGate) {
	// put the new Gate at the back of the vector
	nextGates.push_back(newGate);
}

//add history to the wire
void Wire::addHistory(int newHistory) {
	history.push_back(newHistory);
}