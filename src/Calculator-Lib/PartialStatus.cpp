#include "Status.h"

PartialStatus::PartialStatus() : error_(ErrorTypes::ErrorType::NONE), expected_char('\0') {}

PartialStatus::PartialStatus(ErrorTypes::ErrorType error, char expectedChar) : error_(error), expected_char(expectedChar) {}

ErrorTypes::ErrorType PartialStatus::GetErrorType() const {
	return error_;
}

char PartialStatus::GetExpectedChar() const {
	return expected_char;
}

bool PartialStatus::Failed() const {
	return error_ != ErrorTypes::ErrorType::NONE;
}
