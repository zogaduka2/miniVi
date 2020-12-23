#include <iostream>
#include <string>
#include "LinkedList.h" // ADT list operations
#include <fstream>
#include "Editor.h"
#include "CommandPlus.h"
#include "LinkedStack.h"
#include "Point.h"
using namespace std;
/*
-----This program is a simplified verison of a Vi editor-----
this program opens the file we are inputing from and is able to display and move the cursor through
the users input.
It is also able to insert a line, delete a character (with x, 2x or 3x), delete a line (with dd, 2dd, or 3dd), undo these functions,  */
    
int main(int argc, char* argv[])
{
  
    if (argc > 1) {
        Editor miniVi(argv[1],argv[2]);  // switched from sample.txt to keywords.txt
        miniVi.displayLines();
        miniVi.run();
    }
    else {
        cout << "argc is less than 1, no files were read" << endl;
        exit(1);
    }
  


   
    system("pause");
    return 0;
}  // end main
