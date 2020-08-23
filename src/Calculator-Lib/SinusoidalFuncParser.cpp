#include "InternalParser.h"
#include "SinusoidalFuncParser.h"

SinusoidalFuncParser::SinusoidalFuncParser(Operator oper) :
	oper_(oper) {
	child_parser = make_unique<InternalParser>();
}

PartialStatus SinusoidalFuncParser::ParseFirstChar(const char c) {
	if (c != '{') {
		return PartialStatus(ErrorTypes::ErrorType::MUST_BE, '{');
	}
	return PartialStatus();
}

PartialStatus SinusoidalFuncParser::ParseNextChar(const char c, unique_ptr<BranchNode> &outputNode) {
	if (c == '}' && depth_ == 0) {
		Status status = child_parser->Finalize();
		if (status.Failed()) {
			return PartialStatus(status);
		}

		unique_ptr<ExpTree> tree = child_parser->GetTree();
		if (tree == nullptr) {
			return PartialStatus(ErrorTypes::ErrorType::UNKNOWN);
		}

		outputNode = make_unique<UOperNode>(oper_);
		outputNode->AddChild(tree->GetRoot());
		return PartialStatus();
	}
	else {
		if (c == '{') {
			depth_++;
		}
		else if (c == '}') {
			depth_--;
		}
		Status result = child_parser->ParseNextChar(c);
		return PartialStatus(result);
	}
}
