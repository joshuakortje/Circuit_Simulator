#pragma once

#ifndef EVENT_H
#define EVENT_H

#include "Gate.h"

class Event {
public:
	Event(int newTime, string newWire, int newValue, int newCount);
	int getTime();
	string getWire();
	int getValue();
	int getCount();

	friend bool operator<(const Event &lhs, const Event &rhs);

private:
	int time;
	string wire;
	int value;
	int count;
};

#endif //EVENT_H