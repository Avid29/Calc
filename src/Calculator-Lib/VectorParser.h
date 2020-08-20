#pragma once

#include "IFuncParser.h"
#include "LaTeXParser.h"
#include "TensorNode.h"

class VectorParser : public IFuncParser {
	public:
		VectorParser();

		bool ParseFirstChar(const char c);

		bool ParseNextChar(const char c, unique_ptr<BranchNode> &outputNode);

	private:
		unique_ptr<LaTeXParser> child_parser;
		unique_ptr<TensorNode> vector_;
};
