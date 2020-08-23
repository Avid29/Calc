#pragma once

#include "IFuncParser.h"
#include "InternalParser.h"
#include "TensorNode.h"

class VectorParser : public IFuncParser {
	public:
		VectorParser();

		PartialStatus ParseFirstChar(const char c);

		PartialStatus ParseNextChar(const char c, unique_ptr<BranchNode> &outputNode);

	private:
		unique_ptr<InternalParser> child_parser;
		unique_ptr<TensorNode> vector_;
};
