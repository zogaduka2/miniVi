#include "LinkedList.h"
#include "Point.h"
#include "string"
#include "LinkedStack.h"
#include "CommandPlus.h"
#include "BinarySearchTree.h"
//#include "StackInterface.h"
using namespace std;

#ifndef Editor_H
#define Editor_H

class Editor {



public:
	Editor();
	Editor(string, string);
	void displayLines();
	void run();
	void moveDown();
	void moveUp();
	void moveRight();
	void moveLeft();
	void deleteChar();
	void deleteLine();
	void undo();
	void saveFile();
	void insertLine();
	void currentLine();
	

private:
	string outputFile;
	static const int MAX_SIZE = 60;
	BinarySearchTree<string> bst;
	int numKeywords;
	string keyWords[MAX_SIZE];
	LinkedList<string> List;
	Point position;
	LinkedStack<CommandPlus> undoStack;
};


#endif