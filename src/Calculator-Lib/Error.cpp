#include "Error.h"

Error::Error() : PartialError(ErrorTypes::ErrorType::NONE, '\0'), input_(""), position_(0) {}

Error::Error(PartialError error, std::string input, int position) : 
	PartialError(error.GetErrorType(), error.GetExpectedChar()),
	input_(input),
	position_(position) {}

Error::Error(std::string input, int position) : 
	PartialError(ErrorTypes::ErrorType::NONE, '\0'),
	input_(input),
	position_(position) {}

Error::Error(ErrorTypes::ErrorType error, std::string input, int position, char expectedChar) :
	PartialError(error, expectedChar),
	input_(input),
	position_(position)  {}

std::string Error::GetInput() const {
	return input_;
}

int Error::GetPosition() const {
	return position_;
}