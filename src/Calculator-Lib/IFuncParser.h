#pragma once

#include <memory>

#include "OperNode.h"

using namespace std;

class IFuncParser
{
public:
	virtual bool ParseFirstChar(const char c) = 0;

	virtual bool ParseNextChar(const char c, unique_ptr<BranchNode> &outputNode) = 0;

	virtual string PrintProgress(const IPrinter& printer) const = 0;

protected:
	int depth_ = 0;
};
