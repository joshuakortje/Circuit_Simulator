// Circuit Simulator.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include "Wire.h"
#include "Gate.h"
#include "Event.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <string>

using namespace std;

// Function stubs for parsing files
void print(vector<Wire *> &wireGroup);
void parseLogicFile(string filename, vector<Wire *> &circuitWires, vector<Gate *> &circuitGates);
void updateWireHistory(vector<Wire *> &wireGroup);

priority_queue<Event> parseRuntimeFile(string filename, vector<Wire *> &circuitWires);

using Queue = priority_queue<Event>;

int main() {
	vector<Gate *>		circuitGates;
	vector<Wire *>		circuitWires;
	string filename;
	cout << "Please enter the file name - ex. 'circuit0' or 'circuit1': ";
	cin >> filename;

	//Parse Logic file
	parseLogicFile("circuits/" + filename + ".txt", circuitWires, circuitGates);

	//Parse Runtime file
	Queue q = parseRuntimeFile("circuits/" + filename + "_v.txt", circuitWires);

	//Run Simulation
	int runTime = 0; //Keep track of the time
	while ((!q.empty()) && (runTime <= 60)) {

		//if it is not yet time for the next event, move on
		if (runTime < q.top().getTime()) {
			runTime++;

			//Update history on all the wires
			updateWireHistory(circuitWires);
			continue;
		}

		Event currentE = q.top();
		
		//get the driven gates
		vector<Gate *> driven = currentE.getWire()->getNextGates();

		// check if the current event will generate a new event. If it does then push a new event
		for (int i = 0; i < driven.size(); i++) {
			if (driven.at(i)->checkOutputChange(currentE.getWire(), currentE.getValue())) { //check if the output will change
				q.push(Event((runTime + driven.at(i)->getDelay()), driven.at(i)->getOuput(), driven.at(i)->runGateLogic(currentE.getWire(), currentE.getValue())));
			}
		}

		//exucute the event
		currentE.execute();

		// remove this event from the Queue
		q.pop();
	}

	updateWireHistory(circuitWires);
	print(circuitWires);

    return 0;
}

void updateWireHistory(vector<Wire *> &wireGroup) {
	for (int i = 0; i < wireGroup.size(); i++) {
		wireGroup.at(i)->addHistory(wireGroup.at(i)->getValue());
	}
}

void print(vector<Wire*> &wireGroup) {

	// Find and remove the extra numbers in the wire history
		// This loops through and finds the longest common number where all of the wire's history matches the previous
	int commonMaximum = 60;
	for (int i = 0; i < wireGroup.size(); i++) {

		// If the wire isn't an input or output - we aren't going to log it anyway
			// If you want to include all wires just comment the break out.
		if (!wireGroup.at(i)->getInOut()) break;

		vector<int> curWireHistory = wireGroup.at(i)->getHistory();
		int rear = curWireHistory.back();

		// Loop through each wire's history BACKWARDS and find where the last element doesn't match
		for (int j = curWireHistory.size() - 1; j >= 0; j--) {

			// If the wire doesn't match
			if (curWireHistory.at(j) != rear) {

				// curWireHistory.size() - j gets the amount of length of common numbers and the (-2) accounts for the rear and 2nd to last element
				if (commonMaximum > (curWireHistory.size() - j - 2)) {
					commonMaximum = (curWireHistory.size() - j - 2);
				}
				break;
			}
		}
	}

	// Find the longest string name to help create padding
	int longestString = 0;
	for (int i = 0; i < wireGroup.size(); i++) {
		if (wireGroup.at(i)->getName().length() > longestString) {
			longestString = wireGroup.at(i)->getName().length();
		}
	}

	// Loop through and print each output wire's history
	for (int i = 0; i < wireGroup.size(); i++) {

		// Output name before history
		cout << wireGroup.at(i)->getName();

		for (int a = 0; a < (longestString - wireGroup.at(i)->getName().length()); a++) {
			cout << " ";
		}

		cout << " | ";

		vector<int> currentHistory = wireGroup.at(i)->getHistory();
		for (int p = 0; p < currentHistory.size() - commonMaximum; p++) {
			switch(currentHistory.at(p)) {
			case UNKNOWN:
				cout << "X";
				break;

			case HIGH:
				cout << "-";
				break;

			case LOW:
				cout << "_";
				break;
			}
			cout << " "; // Increase spacing
		}

		// Create a new line to distinguish differnet wires 
		cout << endl;
	}

	// Print timeframe
	for (int b = 0; b < longestString + 3; b++) { // Longest String + 3 accounts for the ' | ' after the wire names
		cout << " ";
	}
	for (int i = 0; i <= 60; i++) {
		if (i % 5 == 0 && i < 10)	cout << i << " ";
		else if (i % 5 == 0)		cout << i;
		else						cout << "- ";
	}
}

void parseLogicFile(string filename, vector<Wire *> &circuitWires, vector<Gate *> &circuitGates) {

	// Variables
	ifstream InCircuitInput;
	string type;

	// Open Circuit File
	InCircuitInput.open(filename);
	if (InCircuitInput.fail()) {
		cout << "Could not find circuit file." << endl;
		exit(1);
	}

	// Get Rid of the First Line
	getline(InCircuitInput, type);

	// Parse Each Line of File
	while (!InCircuitInput.eof()) {

		// Get the New Line
		string curLine;
		getline(InCircuitInput, curLine);

		string type = "";
		istringstream ss(curLine);

		// read type to determine next steps
		ss >> type;

		// Sometimes the file has an extra line at the end
		if (type == "" || curLine == "") break;

		if (type == "INPUT" || type == "OUTPUT") {

			// variables to store new values
			string newName = "";
			int newNumber = 0;
			
			// populate variables
			ss >> newName >> newNumber;

			//add the wire to the vector
			circuitWires.push_back(new Wire(newNumber, newName, true));

		}
		else { // Handles all of the gates
			int delay = -1;
			Wire *input1 = nullptr;
			Wire *input2 = nullptr;
			Wire *output = nullptr;

			int inputName1 = -1;
			int inputName2 = -1;
			int outputName = -1;
			
			string delayType = "ns"; // this should always be "ns"

			// Get Values for Each Variable
			ss >> delay >> delayType >> inputName1 >> inputName2 >> outputName;

			// Loop through each wire and find what wires correspond to the given number
			for (int i = 0; i < circuitWires.size(); i++) {
				if (circuitWires.at(i)->getNumber() == inputName1) input1 = circuitWires.at(i);
				if (circuitWires.at(i)->getNumber() == inputName2) input2 = circuitWires.at(i);
				if (circuitWires.at(i)->getNumber() == outputName) output = circuitWires.at(i);
			}

			// If the wire isn't found aka input1/2 == nullptr, then create a new wire for each input
			if (input1 == nullptr) {
				circuitWires.push_back(new Wire(inputName1, to_string(inputName1), false));
				input1 = circuitWires.back();
			}
			if (input2 == nullptr) {
				circuitWires.push_back(new Wire(inputName2, to_string(inputName2), false));
				input2 = circuitWires.back();
			}
			
			// if there is only one input and one output (for example the NOT gate) - then switch input2 and output
			// The reason (outputName == -1) is because that means the value didn't get pulled in from the file
			if (outputName == -1) {
				output = input2;
				input2 = nullptr;
			}
			// output == nullptr means that the wire doesn't exist because it wasn't found in the for loop that cycled through circuitWires
			else if(output == nullptr) { 
				circuitWires.push_back(new Wire(outputName, to_string(outputName), false));
				output = circuitWires.back();
			}

			// Create gate
			Gate* finalGate = new Gate(type, delay, input1, input2, output);

			// Update the nextGates on the input wires for the gate
			input1->addGate(finalGate);
			if(input2 != nullptr) input2->addGate(finalGate);

			// Add the gate
			circuitGates.push_back(finalGate);
		}
	}
	InCircuitInput.close();
}

Queue parseRuntimeFile(string filename, vector<Wire *> &circuitWires) {
	Queue q;
	ifstream runtimeInput;
	string type;

	// Open Circuit File
	runtimeInput.open(filename);
	if (runtimeInput.fail()) {
		cout << "Could not find circuit file." << endl;
		exit(1);
	}

	// get rid of the first line
	getline(runtimeInput, type);

	// parse each line of the file
	while (!runtimeInput.eof()) {

		string curLine;
		string type = "";
		string name = "";
		int eventTime = -1;
		int eventValue = -1;

		// Get Each Line and make it a string stream ss
		getline(runtimeInput, curLine);
		istringstream ss(curLine);

		// Should always be INPUT
		ss >> type;

		// Handle Extra Lines at EOF
		if (type != "INPUT") break;

		// Get Values for Variables
		ss >> name >> eventTime >> eventValue;

		// Find the wire pointer from the name 
		Wire* finalWire = nullptr;
		for (int i = 0; i < circuitWires.size(); i++) {
			if (circuitWires.at(i)->getName() == name) finalWire = circuitWires.at(i);
		}

		// Add the new Event to the Queue
		q.push(Event(eventTime, finalWire, eventValue));
	}
	runtimeInput.close();

	return q;
}