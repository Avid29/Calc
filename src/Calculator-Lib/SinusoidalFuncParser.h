#pragma once

#include <memory>

#include "IFuncParser.h"
#include "OperNode.h"

using namespace std;

class LaTeXParser;

class SinusoidalFuncParser : public IFuncParser
{
public:
	SinusoidalFuncParser(Operator oper);

	bool ParseFirstChar(const char c);

	bool ParseNextChar(const char c, unique_ptr<OperNode> &outputNode);

private:
	Operator oper_;
	unique_ptr<LaTeXParser> child_parser;
};

