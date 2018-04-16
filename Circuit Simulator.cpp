// Circuit Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Wire.h"
#include "Gate.h"
#include "Input.h"
#include "Output.h"
#include "Event.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <string>

using namespace std;

// Function stubs for parsing files
template<typename T>
void print(vector<T*> wireGroup);
void parseLogicFile(string filename);
priority_queue<Event> parseRuntimeFile(string filename);

//Global variables for building the circuit
vector<Gate *>		circuitGates;
vector<Wire *>		circuitWires;
vector<Input *>		circuitInputs;
vector<Output *>	circuitOutputs;

using Queue = priority_queue<Event>;

int main() {
	string filename;
	cout << "Please enter the file name - ex. 'circuit0' or 'circuit1': ";
	cin >> filename;


	//Parse Logic file
	parseLogicFile("circuits/" + filename + ".txt");
	

	//Parse Runtime file
	Queue q = parseRuntimeFile("circuits/" + filename + "_v.txt");

	//Run
	int runTime = 0; //Keep track of the time
	while ((!q.empty()) && (runTime <= 60)) {
		Event currentE = q.top();
		cout << " -Time: " << currentE.getTime() << " -Value: " << currentE.getValue() << " -Wire: " << currentE.getWire() << " -Count: " << currentE.getCount() << endl;

		//get the driven gates
		vector<Gate *> driven = currentE.getWire()->getNextGates();

		//check if they will generate a new event
		for (int i = 0; i < driven.size(); i++) {
			if (driven.at(i)->checkOutputChange(currentE.getWire(), currentE.getValue())) { //check if the output will change
				//push a new event
				q.push(Event((runTime + driven.at(i)->getDelay()), driven.at(i)->getOuput(), driven.at(i)->runGateLogic(currentE.getWire(), currentE.getValue())));
			}
		}

		//exucute the event
		currentE.execute();

		// Update history
		// Loop through each wire, if it is an output add its current value to the history
		// FIXME: I hate this. Its terribly inefficient, but I don't know of a better way right now.
		for (int a = 0; a < circuitWires.size(); a++) {
			for (int i = 0; i < circuitOutputs.size(); i++) {
				if (circuitWires.at(a)->getName() == circuitOutputs.at(i)->getName()) circuitOutputs.at(i)->addHistory(circuitWires.at(a)->getValue());
			}
			for (int i = 0; i < circuitInputs.size(); i++) {
				if (circuitWires.at(a)->getName() == circuitInputs.at(i)->getName()) circuitInputs.at(i)->addHistory(circuitWires.at(a)->getValue());
			}
		}

		q.pop();
		runTime++;
	}

	// Output -- FIXME There has to be a better way to this.....
	print(circuitInputs);
	print(circuitOutputs);

	// Print timeframe
	cout << "    ";
	for (int i = 0; i <= 60; i++) {
		if (i % 5 == 0) cout << i;
		else if (!(i % 5 == 1 && i >= 10))  cout << "-"; // This accounts for the fact that "i" could take up 2 spots if i >= 10
	}

    return 0;
}

template<typename T>
void print(vector<T*> wireGroup) {
	// Loop through and print each output wire's history
	for (int i = 0; i < wireGroup.size(); i++) {

		// Output name before history
		cout << wireGroup.at(i)->getName() << " | ";

		//for (int j = 0; j < circuitOutputs.at(i)->getHistory().size(); i++) {

		int currentReadHistory = wireGroup.at(i)->readHistory();
		while (currentReadHistory != EMPTY_HISTORY) {
			switch (currentReadHistory) {
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
			currentReadHistory = wireGroup.at(i)->readHistory();
		}

		// Create a new line to distinguish differnet wires 
		cout << endl;
	}
}

void parseLogicFile(string filename) {

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

			//cout << newName << " " << newNumber << endl;

			//add the wire to the vector
			circuitWires.push_back(new Wire(newNumber, newName));

			//add the input/output to the vector
			if (type == "INPUT") {
				circuitInputs.push_back(new Input(newName, circuitWires.back()));
			}
			else {
				circuitOutputs.push_back(new Output(newName));
			}

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
				circuitWires.push_back(new Wire(inputName1, to_string(inputName1)));
				circuitInputs.push_back(new Input(to_string(inputName1), circuitWires.back()));
				input1 = circuitWires.back();
			}
			if (input2 == nullptr) {
				circuitWires.push_back(new Wire(inputName2, to_string(inputName2)));

				// This is the case where there isn't a wire already made for the 2nd input of a gate
				// If it is a NOT gate, then the 2nd input is actually an output. So this if statement fixes it
				if (type == "NOT") {
					circuitOutputs.push_back(new Output(to_string(inputName2)));
				}
				else {
					circuitInputs.push_back(new Input(to_string(inputName2), circuitWires.back()));
				}
				input2 = circuitWires.back();
			}
			
			// if there is only one input and one output (for example the NOT gate) - then switch input2 and output
			// The reason (outputName == -1) is because that means the value didn't get pulled in from the file
			if (outputName == -1) {
				output = input2;
				input2 = nullptr;

				// switch the wire from input to output
				//circuitInputs.pop_back();						// FIXME make sure this is supposed to be commented out
				circuitOutputs.push_back(new Output(to_string(inputName2)));
			}
			// output == nullptr means that the wire doesn't exist because it wasn't found in the for loop that cycled through circuitWires
			else if(output == nullptr) {
				circuitWires.push_back(new Wire(outputName, to_string(outputName)));
				circuitOutputs.push_back(new Output(to_string(outputName)));
			}

			// Create gate
			Gate* finalGate = new Gate(type, delay, input1, input2, output);

			// Update the nextGates on the input wires for the gate
			input1->addGate(finalGate);
			if(input2 != nullptr) input2->addGate(finalGate);

			// Add the gate
			circuitGates.push_back(finalGate);



			// FOR TESTING
			if (input2 == nullptr) {
				outputName = inputName2;
				inputName2 = -1;
			}
			cout << " -Type: " << type << " -Delay: " << delay << " -Delay Type: " << delayType << " -Input One Name: " << inputName1 << " -Input Two Name: " << inputName2;
			cout << " -Output: " << outputName << endl;
		}


	}
	InCircuitInput.close();
}

Queue parseRuntimeFile(string filename) {
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
		for (int i = 0; i < circuitInputs.size(); i++) {
			if (circuitInputs.at(i)->getName() == name) finalWire = circuitInputs.at(i)->getWire();
		}

		// Add the new Event to the Queue
		q.push(Event(eventTime, finalWire, eventValue));

		// FOR TESTING
		cout << " -Name: " << name << " -Time: " << eventTime << " -Value: " << eventValue << endl;

	}
	runtimeInput.close();

	return q;
}