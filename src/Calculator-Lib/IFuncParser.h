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

	virtual Error::ErrorType GetError() const;
protected:
	int depth_ = 0;
	Error::ErrorType error_;

	virtual void EnterErrorState(Error::ErrorType error);
};
