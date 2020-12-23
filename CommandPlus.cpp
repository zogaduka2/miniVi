#include <iostream>
#include <string>
#include "CommandPlus.h"
#include "Point.h"

using namespace std;

CommandPlus::CommandPlus() {}


void CommandPlus::setValue(string x) {

	value = x;

}

string CommandPlus::getValue() const {

	return value;

}

void CommandPlus::setCommand(char c) {

	
	command = c;
}



char CommandPlus::getCommand() const {

	return command;
}


void CommandPlus::setPoint(Point x) {

	userPosition = x;

}
Point CommandPlus::getPoint() {

	return userPosition;

}