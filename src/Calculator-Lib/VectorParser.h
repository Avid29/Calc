#pragma once

#include "IFuncParser.h"
#include "InternalParser.h"
#include "TensorNode.h"

class VectorParser : public IFuncParser {
	public:
		VectorParser();

		bool ParseFirstChar(const char c);

		bool ParseNextChar(const char c, unique_ptr<BranchNode> &outputNode);

		string PrintProgress(const IPrinter& printer) const;
	private:
		unique_ptr<InternalParser> child_parser;
		unique_ptr<TensorNode> vector_;
};
