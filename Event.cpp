#include "stdafx.h"
#include <iostream>
#include <string>
#include "Event.h"


using namespace std;

int Event::runningCount = 0;

Event::Event(int newTime, Wire* newWire, int newValue) : time(newTime), wire(newWire), value(newValue) {

	// This keeps track of how many events have been created and assigns count that number
	// It makes it so we know exactly what order things should go in
	count = runningCount;
	runningCount++;
}

bool operator<(const Event &lhs, const Event &rhs) {
	// by default the queue is a MAX queue, so we reverse the comparison
	// from '<' to '>' (see the return statements) to make it a MIN queue
	if (lhs.getTime() == rhs.getTime()) {
		return lhs.getCount() > rhs.getCount();
	}

	return lhs.getTime() > rhs.getTime();
}

//this will execute the event
void Event::execute() {
	wire->updateWire(value);
}