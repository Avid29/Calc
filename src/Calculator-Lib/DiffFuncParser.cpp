#include "DiffFuncParser.h"
#include "InternalParser.h"

DiffFuncParser::DiffFuncParser() :
	state_(State::OPEN_VAR) {
	depth_ = 0;
	node = make_unique<DiffOperNode>();
	child_parser = make_unique<InternalParser>();
}

PartialError DiffFuncParser::ParseFirstChar(const char c) {
	if (c == '[' && state_ == State::OPEN_VAR) {
		state_ = State::VAR;
		return PartialError();
	}
	else {
		return PartialError(ErrorTypes::ErrorType::MUST_BE, '[');
	}
}

PartialError DiffFuncParser::ParseNextChar(const char c, unique_ptr<BranchNode>& outputNode) {
	switch (state_)
	{
	case State::VAR: {
		if (isalpha(c)) {
			node->SetVariable(make_unique<VarValueNode>(c));
			state_ = State::CLOSING_VAR;
			return PartialError();
		}
		return PartialError(ErrorTypes::ErrorType::DERIVATIVE_MUST_BE_VARIABLE);
	}
	case State::CLOSING_VAR:
		state_ = State::OPEN_EXPRESSION;
		if (c != ']') {
			return PartialError(ErrorTypes::ErrorType::MUST_BE, '[');
		}
		return PartialError();
	case State::OPEN_EXPRESSION:
		state_ = State::EXPRESSION;
		if (c != '{') {
			return PartialError(ErrorTypes::ErrorType::MUST_BE, '{');
		}
		return PartialError();
	case State::EXPRESSION: {
		if (c == '}' && depth_ == 0) {
			Error status = child_parser->Finalize();
			if (status.Occured()) {
				return PartialError(status);
			}

			unique_ptr<ExpTree> tree = child_parser->GetTree();
			if (tree == nullptr) {
				return PartialError(ErrorTypes::ErrorType::UNKNOWN);
			}
			node->AddChild(tree->GetRoot());
			state_ = State::DONE;
			outputNode = move(node);
			return PartialError();
		}
		else {
			if (c == '{') {
				depth_++;
			}
			else if (c == '}'){
				depth_--;
			}
			Error result = child_parser->ParseNextChar(c);
			return PartialError(result);
		}
	}
	case State::DONE:
		return PartialError(ErrorTypes::ErrorType::UNKNOWN);
	}
}
