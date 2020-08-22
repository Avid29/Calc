#include "Error.h"

PartialError::PartialError() : error_(ErrorTypes::ErrorType::NONE), expected_char('\0') {}

PartialError::PartialError(ErrorTypes::ErrorType error, char expectedChar) : error_(error), expected_char(expectedChar) {}

ErrorTypes::ErrorType PartialError::GetErrorType() const {
	return error_;
}

char PartialError::GetExpectedChar() const {
	return expected_char;
}