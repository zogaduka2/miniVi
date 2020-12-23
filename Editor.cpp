#include <iostream>
#include <fstream>
#include <string>
#include "Editor.h"
#include "LinkedList.h"
#include "Point.h"
#include "Node.h"
#include "windows.h"
#include "CommandPlus.h"
#include <conio.h>
#include "LinkedStack.h"
#include "StackInterface.h"
#include <sstream>
#include "BinarySearchTree.h"

using namespace std;


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define escapeKey 27


// set color of keywords
void colorText(int value) {

	COORD coord;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	FlushConsoleInputBuffer(hConsole);

	SetConsoleTextAttribute(hConsole, value + 240);

}


// Sets cursor position
void placeCursorAt(Point coordinate) {
	COORD coord;
	coord.X = coordinate.getX();
	coord.Y = coordinate.getY();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


//deafult constructor
Editor::Editor() :numKeywords(0)
{}


/*constructor that takes name of file and passes it
initializes and fills out the BST with keywordsso that we are
 able to display the keywords on the outuput
 */
Editor::Editor(string textFile, string keywordFileName)
{
	outputFile = textFile;
	ifstream infile(textFile);
	if (!infile) {
		exit(0);
	}
	string str;
	int lineNumber = 1;
	while (!infile.eof()) {
		getline(infile, str);    // put first line in str 
		List.insert(lineNumber, str);  // put string in position
		lineNumber++;
	}

	ifstream keywordFile(keywordFileName);

	numKeywords = 0;
	
	string readLine;
    
    //keyword BST is being filled in by this loop
	while (!keywordFile.eof())
	{
		keywordFile >> readLine;  // get line
		bst.add(readLine);
		
	}
}


//function to sae the file and the changes made
void Editor::saveFile() {

	// open the file the user is working on as an output file
	//ofstream outFile("sample.txt");
	ofstream outFile(outputFile);
	
	// write out all the lines from the linked list
	for (int i = 1; i <= List.getLength(); i++) {
		outFile << List.getEntry(i) << endl;
	}
	outFile.close();


}


// displays the file--as a list implementation
void Editor::displayLines() {

	int uPosition;
	string nextLine, nextWord, line;

	for (uPosition = 1; uPosition <= List.getLength(); uPosition++)
	{
		nextLine = List.getEntry(uPosition);
	
		int i = 0;
		while (i < nextLine.length()) {
			string word;
			// isolate a word at a time (can contain underscores)
			if (isalpha(nextLine[i])) {
				while (isalpha(nextLine[i]) || nextLine[i] == '_') {
					word += nextLine[i];
					i++;
				}
				//if (binarySearch(keyWords, 0, numKeywords-1, word) != -1)
				if((bst.contains(word)) == 0)
					colorText(1);
				else
					colorText(0);
				cout << word;
			}
			else {
				colorText(0);
				cout << nextLine[i];
				i++;
			}}

		cout << endl;
	}
	placeCursorAt(position);

}





/*function that keeps the program running and takes in the commands from the user
*/
 void Editor::run() {


	const char QUIT = 'q';
	const int ESCAPE = 27;
	//char command = _getwch();
	char command;
	Point writePoint(1, List.getLength() + 3);
	do {
		//j, k, l, h, q
		command = _getwch();
		switch (command) {

		case 'j':
		case 80:
			moveDown();
			break;
		case 'k':
		case 72:
			moveUp();
			break;
		case 'l':
		case 77:
			moveRight();
			break;
		case 'h':
		case 75:
			moveLeft();
			break;
		case 'x':
			deleteChar();
			break;
		case 'd':
			char ch;
			if((ch = _getwch()) == 'd')
			deleteLine();
			break;
		case 'u':
			undo();
			break;
		case 'i':
			currentLine();
			insertLine();
			break;
		case '2':
			char delete2;
			if ((delete2 = _getwch()) == 'x') {
				for (int i = 0; i < 2; i++) {
					deleteChar();
				}
			}
			if ((delete2 = _getwch()) == 'd') {
				for (int i = 0; i < 2; i++) {
					deleteLine();
				}
			}
			break;
		case '3':
		char delete3;
		if ((delete3 = _getwch()) == 'x') {
			for (int i = 0; i < 3; i++) {
				deleteChar();
			}
		}
		if ((delete3 = _getwch()) == 'd') {
			for (int i = 0; i < 3; i++) {
				deleteLine();
			}
		}
			break;
		case ':':
			placeCursorAt(writePoint);
			cout << ":";
			char input = _getwch();
			cout << input;
			if (input == 'q') {
				//exit(0);
				return;
			}
			if (input == 'w') {
				saveFile();
				cout << endl;
				cout << "File Saved";
			}
			break;


		}
	} while (command != QUIT);




}
//function to move the cursor up
void Editor::moveUp() {
	//decrease y variable

	if (position.getY() >= 0) {   /// Y equals zero or greater
		if (position.getY() != 0) {   // if Y is not zero 
			position.setY(position.getY() - 1);   // decrease Y
			placeCursorAt(position);   // set position 
		}
		else if (position.getY() == 0) {   // else Y is zero
			position.setY(position.getY());  // set Y
			placeCursorAt(position);  // set position
		}
		else {
			// y is less than zero, revert back to prev position
			position.setY(position.getY() + 1);
			placeCursorAt(position);

		}


	}
}



//function to move the cursor down
void Editor::moveDown() {
	// increase Y variable


	if (position.getY() >= 0 && position.getY() < (List.getLength() - 1)) {  // if Y is greater than or equal to zero
		position.setY(position.getY() + 1);      //increase Y
		placeCursorAt(position);			//set Y
	}


}
//function to move the cursor right
void Editor::moveRight() {
	// Increase X value



	string currentLine = List.getEntry(position.getY() + 1);
	int length = currentLine.length();
	// < length - 1  //<= (length - 2) )
	if (position.getX() >= 0 && position.getX() < (length - 1)) {   // if X is greater or equal to zero

		position.setX(position.getX() + 1);  // Incease x
		placeCursorAt(position);			 // set X

	}


}
//function to move the cursor left
void Editor::moveLeft() {
	// Decrease X variable

	if (position.getX() >= 0) {				// if X is greater than or equal to zero
		position.setX(position.getX() - 1);     // decrease X
		placeCursorAt(position);				// Set X
	}



	if (position.getX() < 0) {					// if X < 0 
		position.setX(position.getX() + 1);		// increase X and set back to last position
		placeCursorAt(position);				// set X
	}

}



//function that deletes a character
void Editor::deleteChar() {

	string currentLine = List.getEntry(position.getY() + 1);



	CommandPlus commandplus;
	commandplus.setCommand('x');

	commandplus.setValue(currentLine);


	Point lastPosition(position.getX(), position.getY());
	commandplus.setPoint(lastPosition);

	undoStack.push(commandplus);




	currentLine.erase(position.getX(), 1);
	List.replace(position.getY() + 1, currentLine);
	system("CLS");
	displayLines();

}


//function that deletes a line
void Editor::deleteLine() {


		string currentLine = List.getEntry(position.getY() + 1);


		CommandPlus commandplus;
		commandplus.setCommand('d');
		commandplus.setValue(currentLine);

		Point lastPosition(position.getX(), position.getY());
		commandplus.setPoint(lastPosition);

		undoStack.push(commandplus);


		List.remove(position.getY() + 1);
		system("CLS");
		displayLines();



}
//function to undo the changes made one by one--using a stack
void Editor::undo() {
	bool stop = false;
	while (!undoStack.isEmpty() && !stop) {

		CommandPlus top = undoStack.peek();
		char command = top.getCommand();
		string currentLine = top.getValue();

		undoStack.pop();
		switch (command) {

		case 'x':
			List.replace(position.getY() + 1, currentLine);
			system("CLS");
			displayLines();
			stop = true;
			break;
		case 'd':
			List.insert(position.getY() + 1, currentLine);
			system("CLS");
			displayLines();
			stop = true;
			break;
		}
	}


}



//function to get the current line--used in the insertLine function
void Editor::currentLine() {

	string currentLine;
	getline(cin, currentLine);

	CommandPlus commandplus;
	commandplus.setCommand('i');
	commandplus.setValue(currentLine);

	Point lastPosition(position.getX(), position.getY());
	commandplus.setPoint(lastPosition);

	undoStack.push(commandplus);

}

//function that inserts a line
void Editor::insertLine() {

	CommandPlus location = undoStack.peek();
	string text = location.getValue();
	Point currentPoint = location.getPoint();


	List.insert(currentPoint.getY() + 1, text);
	system("CLS");
	displayLines();
	saveFile();


}
