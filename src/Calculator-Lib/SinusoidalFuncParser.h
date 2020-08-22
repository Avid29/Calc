#pragma once

#include "IFuncParser.h"
#include "OperNode.h"

using namespace std;

class InternalParser;

class SinusoidalFuncParser : public IFuncParser
{
public:
	SinusoidalFuncParser(Operator oper);

	PartialError ParseFirstChar(const char c);

	PartialError ParseNextChar(const char c, unique_ptr<BranchNode> &outputNode);

private:
	Operator oper_;
	unique_ptr<InternalParser> child_parser;
};

