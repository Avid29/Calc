#include "LaTeXParser.h"
#include "SinusoidalFuncParser.h"

SinusoidalFuncParser::SinusoidalFuncParser(Operator oper) :
	oper_(oper) {
	child_parser = make_unique<LaTeXParser>();
}

bool SinusoidalFuncParser::ParseFirstChar(const char c) {
	return c == '{';
}

bool SinusoidalFuncParser::ParseNextChar(const char c, unique_ptr<OperNode> &outputNode) {
	if (c == '}' && depth_ == 0) {
		unique_ptr<ExpTree> tree = child_parser->FinalizeAndReturn();
		if (tree == nullptr) {
			return false;
		}

		outputNode = make_unique<UOperNode>(oper_);
		outputNode->AddChild(tree->GetRoot());
		return true;
	}
	else {
		if (c == '{') {
			depth_++;
		}
		else if (c == '}') {
			depth_--;
		}
		return child_parser->ParseNextChar(c);
	}
}
