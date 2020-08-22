#pragma once

#include "IFuncParser.h"

Error::ErrorType IFuncParser::GetError() const {
	return error_;
}

void IFuncParser::EnterErrorState(Error::ErrorType error) {
	error_ = error;
}
