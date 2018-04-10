// Circuit Simulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Wire.h"
#include "Gate.h"
#include "Input.h"
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
		
		if (type == "INPUT" || type == "OUTPUT") {

			// variables to store new values
			string newName = "";
			int newNumber = 0;
			
			// populate variables
			ss >> newName >> newNumber;

			//cout << newName << " " << newNumber << endl;

			if (type == "INPUT") {
				//add the wire to the vector
				circuitWires.push_back(new Wire(newNumber));
			}
			else {

			}

			//add the input to the vector
			//circuitInputs.push_back(new Input(newName, circuitWires.back()));
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