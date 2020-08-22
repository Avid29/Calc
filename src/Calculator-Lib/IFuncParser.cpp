#pragma once

#include "IFuncParser.h"

PartialError IFuncParser::GetError() const {
	return error_;
}

void IFuncParser::EnterErrorState(ErrorTypes::ErrorType error, char expectedChar) {
	error_ = PartialError(error, expectedChar);
}
