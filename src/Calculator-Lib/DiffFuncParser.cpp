#include "DiffFuncParser.h"
#include "InternalParser.h"

DiffFuncParser::DiffFuncParser() :
	state_(State::OPEN_VAR) {
	depth_ = 0;
	node = make_unique<DiffOperNode>();
	child_parser = make_unique<InternalParser>();
}

bool DiffFuncParser::ParseFirstChar(const char c) {
	if (c == '[' && state_ == State::OPEN_VAR) {
		state_ = State::VAR;
		return true;
	}
	else {
		return false;
	}
}

bool DiffFuncParser::ParseNextChar(const char c, unique_ptr<BranchNode>& outputNode) {
	switch (state_)
	{
	case State::VAR: {
		if (isalpha(c)) {
			node->SetVariable(make_unique<VarValueNode>(c));
			state_ = State::CLOSING_VAR;
			return true;
		}
		return false;
	}
	case State::CLOSING_VAR:
		state_ = State::OPEN_EXPRESSION;
		return c == ']';
	case State::OPEN_EXPRESSION:
		state_ = State::EXPRESSION;
		return c == '{';
	case State::EXPRESSION: {
		if (c == '}' && depth_ == 0) {
			unique_ptr<ExpTree> tree = child_parser->FinalizeAndReturn();
			EnterErrorState(child_parser->GetError().GetErrorType());
			if (tree == nullptr) {
				return false;
			}
			node->AddChild(tree->GetRoot());
			state_ = State::DONE;
			outputNode = move(node);
			return true;
		}
		else {
			if (c == '{') {
				depth_++;
			}
			else if (c == '}'){
				depth_--;
			}
			bool result = child_parser->ParseNextChar(c);
			if (!result) {
				EnterErrorState(child_parser->GetError().GetErrorType());
			}
			return result;
		}
	}
	case State::DONE:
		return false;
	}
}
