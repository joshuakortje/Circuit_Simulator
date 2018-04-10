#pragma once
#include <iostream>
#include <string>

class Input {
public:
	Input(std::string newName, int newValue);

	std::string getName() { return name; }

	void setValue(int newValue);
private:
	std::string name;
	int value;
};