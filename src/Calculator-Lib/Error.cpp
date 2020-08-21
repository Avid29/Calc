#include "Error.h"

Error::Error() : error_(ErrorType::NONE), input_(""), position_(0) {}

Error::Error(ErrorType error, std::string input, int position) : error_(error), input_(input), position_(position) {}

Error::ErrorType Error::GetErrorType() const {
	return error_;
}

std::string Error::GetInput() const {
	return input_;
}

int Error::GetPosition() const {
	return position_;
}