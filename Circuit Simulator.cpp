// Circuit Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Wire.h"
#include "Gate.h"
#include "Input.h"
#include "Output.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

//function for parsing logic file
void parseLogicFile();

//functions for finding letters and numbers
//int findNumber(string sample, int start = 0);
//int findLetter(string sample, int start = 0);

//Global variables for building the circuit
vector<Gate *> circuitGates;
vector<Wire *> circuitWires;
vector<Input *> circuitInputs;
vector<Output *> circuitOutputs;

int main() {
	//Parse Logic file
	parseLogicFile();
	
	//Parse Runtime file

	//Run

	//Output


    return 0;
}

void parseLogicFile() {

	//variables
	string filename;
	ifstream InCircuitInput;
	string type;

	//get the file
	cout << "Please enter the file name: ";
	cin >> filename;

	//open circuit file
	InCircuitInput.open(filename);
	if (InCircuitInput.fail()) {
		cout << "Could not find circuit file." << endl;
		exit(1);
	}

	//get rid of the first line
	getline(InCircuitInput, type);

	//parse all the lines
	/*while (!InCircuitInput.eof()) {
		//get the type of object that is held on this line
		InCircuitInput >> type;
	}*/

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
				circuitOutputs.push_back(new Output(newName, circuitWires.back()));
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
				circuitInputs.push_back(new Input(to_string(inputName1), circuitWires.back()));
				input1 = circuitWires.back();
			}
			else if (input2 == nullptr) {
				// Make a new input wire
				circuitWires.push_back(new Wire(inputName2));
				circuitInputs.push_back(new Input(to_string(inputName2), circuitWires.back()));
				input2 = circuitWires.back();
			}
			
			// if there is only one input and one output - then switch input2 and output
			if (output == nullptr) {
				output = input2;
				input2 = nullptr;

				// switch the wire from input to output
				circuitInputs.pop_back();
				circuitOutputs.push_back(new Output(to_string(inputName2), circuitWires.back()));
			}


			circuitGates.push_back(new Gate(type, delay, input1, input2, output));
		}


	}




	/*
	//parse all the lines
	while (!InCircuitInput.eof()) {
		//get the new line
		getline(cin, circuitInput);

		//check for an empty line at the end
		if (!isalpha(circuitInput[0])) {
			break;
		}

		//determine what the line holds
		if (circuitInput.substr(0, 5) == "INPUT") { // input line
													//find the start of the first letter
			int start = findLetter(circuitInput, 6);

			//get the portion of the line after that point
			string lineLeft = circuitInput.substr(start, circuitInput.length());

			//get the Name of the Input
			string newName = lineLeft.substr(0, lineLeft.find(" "));

			//find the start of the number
			start = findNumber(lineLeft, lineLeft.find(" "));

			//get the next version of the string
			lineLeft = lineLeft.substr(start, lineLeft.length());

			//find the number of the Wire
			int newNumber = stoi(lineLeft.substr(0, lineLeft.find('/n')));

			//add the wire to the vector
			circuitWires.push_back(new Wire(newNumber));

			//add the input to the vector
			circuitInputs.push_back(new Input(newName, circuitWires.back()));
		}
		else if (circuitInput.substr(0, 6) == "OUTPUT") { // output line

		}
		else { // gate line

		}
	}
	*/

	InCircuitInput.close();
}

/*
int findNumber(string sample, int start) {
	//iterate through the string to find the first number
	for (int i = start; i < sample.length(); i++) {
		//return the index of the first number
		if (isdigit(sample[i])) {
			return i;
		}
	}

	//not found so return -1
	return -1;
}

int findLetter(string sample, int start) {
	//iterate through the string to find the first letter
	for (int i = start; i < sample.length(); i++) {
		//return the index of the first letter
		if (isalpha(sample[i])) {
			return i;
		}
	}

	//not found so return -1
	return -1;
}
*/