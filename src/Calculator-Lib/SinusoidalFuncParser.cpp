#include "InternalParser.h"
#include "SinusoidalFuncParser.h"

SinusoidalFuncParser::SinusoidalFuncParser(Operator oper) :
	oper_(oper) {
	child_parser = make_unique<InternalParser>();
}

bool SinusoidalFuncParser::ParseFirstChar(const char c) {
	return c == '{';
}

bool SinusoidalFuncParser::ParseNextChar(const char c, unique_ptr<BranchNode> &outputNode) {
	if (c == '}' && depth_ == 0) {
		unique_ptr<ExpTree> tree = child_parser->FinalizeAndReturn();
		EnterErrorState(child_parser->GetError().GetErrorType());
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
		bool result = child_parser->ParseNextChar(c);
		if (!result) {
			EnterErrorState(child_parser->GetError().GetErrorType());
		}
		return result;
	}
}
