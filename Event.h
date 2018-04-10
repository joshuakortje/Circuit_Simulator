#pragma once

#ifndef EVENT_H
#define EVENT_H

#include "Gate.h"

class Event {

private:
	int time;
	string wire;
	int value;
	int count;
};

#endif //EVENT_H