#pragma once
#ifndef NOT_FOUND_EXCEPTION_
#define NOT_FOUND_EXCEPTION_
#include <stdexcept>
#include <string> // For string data type

using namespace std;

class NotFoundException : public logic_error
{
public:
	NotFoundException(const string& message = "");
}; // end NotFoundException.h
#endif

