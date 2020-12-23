#include "LinkedList.h"
#include "Point.h"
#include "string"


using namespace std;

#ifndef CommandPlus_H
#define CommandPlus_H


class CommandPlus {


public:
	CommandPlus();
	void setCommand(char);
	char getCommand() const;
	void setValue(string);
	string getValue() const;
	void setPoint(Point);
	Point getPoint();
	

private:
	Point userPosition;
	char command;
	string value;
	
};









#endif