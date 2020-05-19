#include "DiffFuncParser.h"
#include "LaTeXParser.h"

DiffFuncParser::DiffFuncParser() :
	state_(State::OPEN_VAR) {
	depth_ = 0;
	child_parser = make_unique<LaTeXParser>();
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

bool DiffFuncParser::ParseNextChar(const char c, unique_ptr<OperNode>& outputNode) {
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
			return child_parser->ParseNextChar(c);
		}
	}
	case State::DONE:
		return false;
	}
}
