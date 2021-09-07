#include "Status.h"

Status::Status() : PartialStatus(ErrorTypes::ErrorType::NONE, '\0'), input_(""), position_(0) {}

Status::Status(PartialStatus error, std::string input, int position) : 
	PartialStatus(error.GetErrorType(), error.GetExpectedChar()),
	input_(input),
	position_(position) {}

Status::Status(std::string input, int position) : 
	PartialStatus(ErrorTypes::ErrorType::NONE, '\0'),
	input_(input),
	position_(position) {}

Status::Status(ErrorTypes::ErrorType error, std::string input, int position, char expectedChar) :
	PartialStatus(error, expectedChar),
	input_(input),
	position_(position)  {}

std::string Status::GetInput() const {
	return input_;
}

int Status::GetPosition() const {
	return position_;
}