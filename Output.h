#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include "Wire.h"

using namespace std;

class Output {
public:
	Output(string newName);
	void setValue(int newValue);	
	string		getName()		{ return name; }
	int			getValue()		{ return value; }
	//vector<int> getHistory()	{ return history; } //Do we need this??
	void addHistory(int newHistory);
	int readHistory();

private:
	string name;
	int value;
	vector<int> history;
};


#endif //OUTPUT_H