#pragma once

#include <memory>

#include "Error.h"
#include "OperNode.h"

using namespace std;

class IFuncParser
{
public:
	virtual bool ParseFirstChar(const char c) = 0;

	virtual bool ParseNextChar(const char c, unique_ptr<BranchNode> &outputNode) = 0;

	virtual PartialError GetError() const;
protected:
	int depth_ = 0;
	PartialError error_;

	virtual void EnterErrorState(Error error);

	virtual void EnterErrorState(ErrorTypes::ErrorType error, char expectedChar = '\0');
};
