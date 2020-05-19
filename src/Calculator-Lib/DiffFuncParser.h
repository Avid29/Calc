#pragma once

#include "IFuncParser.h"
#include "OperNode.h"
#include "DiffOperNode.h"

class LaTeXParser;

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

	bool ParseFirstChar(const char c);

	bool ParseNextChar(const char c, unique_ptr<OperNode>& outputNode);

private:
	State state_;
	unique_ptr<DiffOperNode> node;
	unique_ptr<LaTeXParser> child_parser;
};

