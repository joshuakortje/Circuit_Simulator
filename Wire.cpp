#include "stdafx.h"
#include "Wire.h"
#include "Gate.h"

// Constructor
Wire::Wire(int newNumber) : number(newNumber) {
	// intitialize the value and number
	//there are no known gates so we leave the vector empty
	value = UNKNOWN;
}

// Destructor
Wire::~Wire() {

}

// Gets the value of the Wire
int Wire::getValue(){
	// return the value on the Wire
	return value;
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
