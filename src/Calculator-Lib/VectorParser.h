#pragma once

#include "IFuncParser.h"
#include "InternalParser.h"
#include "TensorNode.h"

class VectorParser : public IFuncParser {
	public:
		VectorParser();

		PartialError ParseFirstChar(const char c);

		PartialError ParseNextChar(const char c, unique_ptr<BranchNode> &outputNode);

	private:
		unique_ptr<InternalParser> child_parser;
		unique_ptr<TensorNode> vector_;
};
