#pragma once

#include <memory>

#include "Status.h"
#include "OperNode.h"

using namespace std;

class IFuncParser
{
public:
	virtual PartialStatus ParseFirstChar(const char c) = 0;

	virtual PartialStatus ParseNextChar(const char c, unique_ptr<BranchNode> &outputNode) = 0;
protected:
	int depth_ = 0;
};
