#include "InternalParser.h"
#include "SinusoidalFuncParser.h"

SinusoidalFuncParser::SinusoidalFuncParser(Operator oper) :
	oper_(oper) {
	child_parser = make_unique<InternalParser>();
}

PartialError SinusoidalFuncParser::ParseFirstChar(const char c) {
	if (c != '{') {
		return PartialError(ErrorTypes::ErrorType::MUST_BE, '{');
	}
	return PartialError();
}

PartialError SinusoidalFuncParser::ParseNextChar(const char c, unique_ptr<BranchNode> &outputNode) {
	if (c == '}' && depth_ == 0) {
		Error status = child_parser->Finalize();
		if (status.Occured()) {
			return PartialError(status);
		}

		unique_ptr<ExpTree> tree = child_parser->GetTree();
		if (tree == nullptr) {
			return PartialError(ErrorTypes::ErrorType::UNKNOWN);
		}

		outputNode = make_unique<UOperNode>(oper_);
		outputNode->AddChild(tree->GetRoot());
		return PartialError();
	}
	else {
		if (c == '{') {
			depth_++;
		}
		else if (c == '}') {
			depth_--;
		}
		Error result = child_parser->ParseNextChar(c);
		return PartialError(result);
	}
}
