#pragma once

#include "IFuncParser.h"
#include "OperNode.h"
#include "IntegralOperNode.h"

class InternalParser;

class IntegralFuncParser : public IFuncParser
{
public:
	enum class State {
		OPEN_VAR,
		VAR,
		CLOSING_VAR,
		LOWER,
		UPPER,
		OPEN_EXPRESSION,
		EXPRESSION,
		DONE
	};

	IntegralFuncParser();

	PartialStatus ParseFirstChar(const char c);

	PartialStatus ParseNextChar(const char c, unique_ptr<BranchNode>& outputNode);

private:
	State state_;
	unique_ptr<IntegralOperNode> node;
	unique_ptr<InternalParser> child_parser;
};
