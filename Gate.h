#ifndef GATE_H
#define GATE_H

#include <string>
#include <vector>

using namespace std;

class Wire;

class Gate {
public:
	
	// Constructor
	Gate(string newType, int newDelay, Wire *newInput1, Wire *newInput2, Wire *newOutput);
	
	// Member functions
	bool checkOutputChange(Wire *changedWire, int newValue);
	int runGateLogic(Wire *changedWire = nullptr, int newValue = 0);

	// Getters
	int		getDelay()	const { return delay;	}
	Wire*	getOuput()	const { return output;	}

private:
	string type;
	int delay;
	Wire *input1;
	Wire *input2;
	Wire *output;
};
#endif