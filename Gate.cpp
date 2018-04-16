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

// get the type of Gate
string Gate::getType()
{
	//return the type
	return type;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//We probably don't need this because the simulator should be able to update the wires directly
//Update the Gate
void Gate::updateGate() {
	// give the output wire the new value from the Gate logic
	output->updateWire(runGateLogic());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//returns the delay of the gate
int Gate::getDelay() {
	return delay;
}

//returns the output gate
Wire* Gate::getOuput() {
	return output;
}

// check if the output will change
bool Gate::checkOutputChange(Wire *changedWire, int newValue) {
	//if the current output is the same as the calculated output no change
	if (runGateLogic() == runGateLogic(changedWire, newValue)) {
		return false;
	}
	else {
		//there needs to be a change in output
		return true;
	}
}

// Gate logic
int Gate::runGateLogic(Wire *changedWire, int newValue) {
	//account for a possible change in one of the wires
	//default scenario is with no changed wire
	int in1 = input1->getValue();
	int in2;
	if (type != "NOT") { // make sure to account for the 1 input gate
		in2 = input2->getValue();
	}
	if (changedWire != nullptr) { //watch out for when input2 is a nullptr (NOT gate)
		if (changedWire == input1) { //the first wire was changed
			in1 = newValue;
		}
		else if (changedWire == input2) { // the secound wire was changed
			in2 = newValue;
		}
	}

	if (type == "NOT") { // NOT gates
		if (in1 == LOW) {
			return HIGH;
		}
		else if (in1 == HIGH) {
			return LOW;
		}
		else {
			return UNKNOWN;
		}
	}
	else if ((type == "AND") || (type == "NAND")) { // AND or NAND gates
		if ((in1 == LOW) || (in2 == LOW)) { //either one is low
			if (type == "AND") {
				return LOW;
			}
			else {// must be NAND
				return HIGH;
			}
		}
		else if ((in1 == HIGH) && (in2 == HIGH)) { // both high
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
		if ((in1 == HIGH) || (in2 == HIGH)) { //either one is high
			if (type == "OR") {
				return HIGH;
			}
			else { //must be a NOR gate
				return LOW;
			}
		}
		else if ((in1 == LOW) && (in2 == LOW)) { //both are low
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
		if ((in1 == UNKNOWN) || (in2 == UNKNOWN)) { //if either one is unknown we don't have enough info
			return UNKNOWN;
		}
		else if(in1 == in2) { //inputs are the same
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//We probably don't need this because we could call reunGateLogic() directly
//get the current output
int Gate::getCurrentOutput() {
	//return the value of the output Wire
	return runGateLogic();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////