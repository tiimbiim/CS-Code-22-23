#include <String>
#include "exceptions.h"
#include <stdexcept>


	InvalidSize::InvalidSize(const char* errorMessage) : runtime_error(errorMessage) {}

	StackFull::StackFull(const char* errorMessage, int value) : runtime_error(errorMessage), errorVal(value) {}
	int StackFull::getValue() { return errorVal; }

	StackEmpty::StackEmpty(const char* errorMessage) : runtime_error(errorMessage) {}


