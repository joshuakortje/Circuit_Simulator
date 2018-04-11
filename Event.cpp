#include "stdafx.h"
#include <iostream>
#include <string>
#include "Event.h"


using namespace std;

/*Event::Event(int newTime, string newWire, int newValue, int newCount) : time(newTime), wire(newWire), value(newValue), count(newCount) {
	// Empty - because everything is already done in base initialization
}*/
Event::Event(int newTime, string newWire, int newValue) : time(newTime), wire(newWire), value(newValue) {
	// Empty - because everything is already done in base initialization
}

bool operator<(const Event &lhs, const Event &rhs) {
	// by default the queue is a MAX queue, so we reverse the comparison
	// from '<' to '>' (see the return statements) to make it a MIN queue
	if (lhs.getTime() == rhs.getTime()) {
		return lhs.getCount() > rhs.getCount();
	}

	return lhs.getTime() > rhs.getTime();
}