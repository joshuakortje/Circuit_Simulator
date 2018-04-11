#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
public:
	Event(int newTime, std::string newWire, int newValue);
	int			getTime()	const { return time; } 
	std::string	getWire()	const { return wire; } 
	int			getValue()	const { return value; } 
	int			getCount()	const { return count; } 

	friend bool operator<(const Event &lhs, const Event &rhs);

private:
	int time;
	std::string wire;
	int value;
	int count;

	static int runningCount;
};

#endif //EVENT_H