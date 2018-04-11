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

//function for parsing logic file
void parseLogicFile(string filename);
priority_queue<Event> parseRuntimeFile(string filename);

//functions for finding letters and numbers
//int findNumber(string sample, int start = 0);
//int findLetter(string sample, int start = 0);

//Global variables for building the circuit
vector<Gate *> circuitGates;
vector<Wire *> circuitWires;
vector<Input *> circuitInputs;
vector<Output *> circuitOutputs;

using Queue = priority_queue<Event>;

int main() {
	string filename;
	cout << "Please enter the file name: ";
	cin >> filename;


	//Parse Logic file
	parseLogicFile("circuits/" + filename + ".txt");
	

	//Parse Runtime file
	Queue q = parseRuntimeFile("circuits/" + filename + "_v.txt");

	//Run
	while (!q.empty()) {
		Event current = q.top();
		cout << "Time: " << current.getTime() << " -Value: " << current.getValue() << " -Wire: " << current.getWire() << " -Count: " << current.getCount() << endl;
		q.pop();
	}

	cout << endl;
	//Output


    return 0;
}

void parseLogicFile(string filename) {

	//variables
	ifstream InCircuitInput;
	string type;

	//open circuit file
	InCircuitInput.open(filename);
	if (InCircuitInput.fail()) {
		cout << "Could not find circuit file." << endl;
		exit(1);
	}

	//get rid of the first line
	getline(InCircuitInput, type);

	// parse each line of file
	while (!InCircuitInput.eof()) {

		// get the new line
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
			circuitWires.push_back(new Wire(newNumber));

			//add the input/output to the vector
			if (type == "INPUT") {
				circuitInputs.push_back(new Input(newName, circuitWires.back()));
			}
			else {
				circuitOutputs.push_back(new Output(newName));
			}

		}
		else { // Handles all of the gates
			int delay;
			Wire *input1 = nullptr;
			Wire *input2 = nullptr;
			Wire *output = nullptr;

			int inputName1 = -1;
			int inputName2 = -1;
			int outputName = -1;
			
			string delayType = "ns"; // this should always be "ns"
			ss >> delay >> delayType >> inputName1 >> inputName2 >> outputName;

			
			cout << "Type: " << type << "-Delay: " << delay << " -Delay type: " << delayType << " -input one name: " << inputName1 << " -input two name: " << inputName2;
			cout << " -output: " << outputName << endl;

			for (int i = 0; i < circuitWires.size(); i++) {
				if (circuitWires.at(i)->getNumber() == inputName1) input1 = circuitWires.at(i);
				if (circuitWires.at(i)->getNumber() == inputName2) input2 = circuitWires.at(i);
				if (circuitWires.at(i)->getNumber() == outputName) output = circuitWires.at(i);
			}

			if (input1 == nullptr) {
				// Make a new input wire
				circuitWires.push_back(new Wire(inputName1));
				circuitInputs.push_back(new Input(to_string(inputName1), circuitWires.back())); // TODO: change and get rid of the name for the wire
				input1 = circuitWires.back();
			}
			else if (input2 == nullptr) {
				// Make a new input wire
				circuitWires.push_back(new Wire(inputName2));

				if (type == "NOT") {
					circuitOutputs.push_back(new Output(to_string(inputName2)));
				}
				else {
					circuitInputs.push_back(new Input(to_string(inputName2), circuitWires.back())); // TODO: change and get rid of the name for the wire
				}
				input2 = circuitWires.back();
			}
			
			// if there is only one input and one output - then switch input2 and output
			if (output == nullptr) {
				output = input2;
				input2 = nullptr;

				// switch the wire from input to output
				circuitInputs.pop_back();
				circuitOutputs.push_back(new Output(to_string(inputName2)));
			}


			circuitGates.push_back(new Gate(type, delay, input1, input2, output));
		}


	}
	InCircuitInput.close();
}

Queue parseRuntimeFile(string filename) {
	Queue q;
	ifstream runtimeInput;
	string type;

	//open circuit file
	runtimeInput.open(filename);
	if (runtimeInput.fail()) {
		cout << "Could not find circuit file." << endl;
		exit(1);
	}

	//get rid of the first line
	getline(runtimeInput, type);

	// parse each line of the file
	while (!runtimeInput.eof()) {
		string curLine;
		getline(runtimeInput, curLine);

		string type = "";
		istringstream ss(curLine);

		string name = "";
		int eventTime = -1;
		int eventValue = -1;

		ss >> type; // Should always be INPUT

		if (type != "INPUT") break; // handles extra lines at eof

		ss >> name >> eventTime >> eventValue;

		cout << "Name: " << name << " -Time: " << eventTime << " -Value: " << eventValue << endl;

		q.push(Event(eventTime, name, eventValue));

	}
	runtimeInput.close();

	return q;
}

