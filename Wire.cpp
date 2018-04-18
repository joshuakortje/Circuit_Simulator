#include "stdafx.h"
#include "Wire.h"
#include "Gate.h"

// Constructor
Wire::Wire(int newNumber, string name, bool InOut) : number(newNumber), name(name), isInOut(InOut) {
	// intitialize the value and number
	//there are no known gates so we leave the vector empty
	value = UNKNOWN;
}

// Gets the value of the Wire
int Wire::getValue(){
	// return the value on the Wire
	return value;
}

// checks if the wire is an input or output
bool Wire::getInOut() {
	// returns true if it is an input or output wire
	return isInOut;
}

// Changes the Wire value
void Wire::updateWire(int newValue){
	//give the Wire the updated value
	value = newValue;
}

// Adds a gate to the end of the Wire
void Wire::addGate(Gate * newGate){
	// put the new Gate at the back of the vector
	nextGates.push_back(newGate);
}

// returns all the gates driven by the wire
vector<Gate *> Wire::getNextGates() {
	return nextGates;
}

//add history to the wire
void Wire::addHistory(int newHistory) {
	history.push_back(newHistory);
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
