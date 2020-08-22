#pragma once

#include <memory>

#include "Error.h"
#include "OperNode.h"

using namespace std;

class IFuncParser
{
public:
	virtual PartialError ParseFirstChar(const char c) = 0;

	virtual PartialError ParseNextChar(const char c, unique_ptr<BranchNode> &outputNode) = 0;
protected:
	int depth_ = 0;
};
