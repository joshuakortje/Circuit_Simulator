#include "stdafx.h"
#include "Gate.h"
#include "Wire.h"

// Constructor
Gate::Gate(string newType, int newDelay, Wire *newInput1, Wire *newInput2, Wire *newOutput) {
	//initilize the data members
	type = newType;
	delay = newDelay;
	input1 = newInput1;
	input2 = newInput2; //Note: for a NOT gate we only have 1 input so this is NULL
	output = newOutput;
}

// Destructor
Gate::~Gate() {

}

// get the type of Gate
string Gate::getType()
{
	//return the type
	return type;
}

//Update the Gate
void Gate::updateGate() {
	// give the output wire the new value from the Gate logic
	output->updateWire(runGateLogic());
}

// check if the output will change
bool Gate::checkOutputChange() {
	//if the current output is the same as the calculated output no change
	if (getCurrentOutput() == runGateLogic()) {
		return false;
	}
	else {
		//there needs to be a change in output
		return true;
	}
}

// Gate logic
int Gate::runGateLogic() {
	if (type == "NOT") { // NOT gates
		if (input1->getValue() == LOW) {
			return HIGH;
		}
		else if (input1->getValue() == HIGH) {
			return LOW;
		}
		else {
			return UNKNOWN;
		}
	}
	else if ((type == "AND") || (type == "NAND")) { // AND or NAND gates
		if ((input1->getValue() == LOW) || (input2->getValue() == LOW)) { //either one is low
			if (type == "AND") {
				return LOW;
			}
			else {// must be NAND
				return HIGH;
			}
		}
		else if ((input1->getValue() == HIGH) && (input2->getValue() == HIGH)) { // both high
			if (type == "AND") {
				return HIGH;
			}
			else {
				return LOW;
			}
		}
		else {//must be a high and unknown
			return UNKNOWN;
		}
	}
	else if ((type == "OR") || (type == "NOR")) { // OR and NOR gates
		if ((input1->getValue() == HIGH) || (input2->getValue() == HIGH)) { //either one is high
			if (type == "OR") {
				return HIGH;
			}
			else { //must be a NOR gate
				return LOW;
			}
		}
		else if ((input1->getValue() == LOW) && (input2->getValue() == LOW)) { //both are low
			if (type == "OR") {
				return LOW;
			}
			else {
				return HIGH;
			}
		}
		else {//must be low and unknown
			return UNKNOWN;
		}
	}
	else { // XOR and XNOR gates
		if ((input1->getValue() == UNKNOWN) || (input2->getValue() == UNKNOWN)) { //if either one is unknown we don't have enough info
			return UNKNOWN;
		}
		else if(input1->getValue() == input2->getValue()) { //inputs are the same
			if (type == "XOR") {
				return LOW;
			}
			else { //must be XNOR
				return HIGH;
			}
		}
		else { //inputs must be different
			if (type == "XOR") {
				return HIGH;
			}
			else {
				return LOW;
			}
		}
	}
}

//get the current output
int Gate::getCurrentOutput() {
	//return the value of the output Wire
	return output->getValue();
}
