#include "NotFoundException.h"

using namespace std;

NotFoundException::NotFoundException(const string& message)
	: logic_error("NotFoundException Violated Exception: " + message)
{
}  // end constructor
// end NotFoundException.cpp