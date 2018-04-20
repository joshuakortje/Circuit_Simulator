#ifndef WIRE_H
#define WIRE_H

#include <vector>
#include <string>
using namespace std;

class Gate;
const int HIGH = 1;
const int LOW = 0;
const int UNKNOWN = -1;
const int EMPTY_HISTORY = -2;

class Wire {
public:

	// Constructor
	Wire(int newNumber, string name, bool InOut);

	// Member Functions
	void updateWire( int newValue);
	int readHistory();

	// Adders
	void addGate(Gate* newGate);
	void addHistory(int newHistory);

	// Getters
	bool			getInOut()		const { return isInOut;		}
	int				getValue()		const { return value;		}
	int				getNumber()		const { return number;		}
	string			getName()		const { return name;		}
	vector<Gate *>	getNextGates()	const { return nextGates;	}

private:
	bool isInOut;				// True for inputs and outputs
	int value;
	int number;
	string name;
	vector<Gate *> nextGates;	// List of all gates driven by wire
	vector<int> history;
};

#endif