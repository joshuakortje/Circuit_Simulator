#ifndef EVENT_H
#define EVENT_H

#include <string>
#include "Wire.h"
using namespace std;

class Event {
public:

	// Constructor
	Event(int newTime, Wire* newWire, int newValue);

	// Member Functions
	void execute();

	// Getters
	int			getTime()	const { return time; } 
	Wire*		getWire()	const { return wire; } 
	int			getValue()	const { return value; } 
	int			getCount()	const { return count; } 

	// Friend Functions
	friend bool operator<(const Event &lhs, const Event &rhs);

private:
	int time;
	Wire* wire;
	int value;
	int count;

	static int runningCount;
};

#endif //EVENT_H