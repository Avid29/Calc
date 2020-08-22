#pragma once

#include "IFuncParser.h"
#include "OperNode.h"
#include "DiffOperNode.h"

class InternalParser;

class DiffFuncParser : public IFuncParser
{
public:
	enum class State {
		OPEN_VAR,
		VAR,
		CLOSING_VAR,
		OPEN_EXPRESSION,
		EXPRESSION,
		DONE
	};

	DiffFuncParser();

	PartialStatus ParseFirstChar(const char c);

	PartialStatus ParseNextChar(const char c, unique_ptr<BranchNode>& outputNode);

private:
	State state_;
	unique_ptr<DiffOperNode> node;
	unique_ptr<InternalParser> child_parser;
};
