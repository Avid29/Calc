#include "IntegralFuncParser.h"
#include "InternalParser.h"

IntegralFuncParser::IntegralFuncParser() : state_(State::OPEN_VAR) {
	depth_ = 0;
	node = make_unique<IntegralOperNode>();
	child_parser = make_unique<InternalParser>();
}

PartialStatus IntegralFuncParser::ParseFirstChar(const char c) {
	if (c == '[' && state_ == State::OPEN_VAR) {
		state_ = State::VAR;
		return PartialStatus();
	}
	else {
		return PartialStatus(ErrorTypes::ErrorType::MUST_BE, '[');
	}
}

PartialStatus IntegralFuncParser::ParseNextChar(const char c, unique_ptr<BranchNode>& outputNode) {
	switch (state_)
	{
	case State::VAR: {
		if (isalpha(c)) {
			node->SetVariable(make_unique<VarValueNode>(c));
			state_ = State::CLOSING_VAR;
			return PartialStatus();
		}
		return PartialStatus(ErrorTypes::ErrorType::DERIVATIVE_MUST_BE_VARIABLE);
	}
	case State::CLOSING_VAR:
		if (c == ']')
		{
			state_ = State::OPEN_EXPRESSION;
			return PartialStatus();
		}
		if (c == ',')
		{
			state_ = State::LOWER;
			return PartialStatus();
		}
		return PartialStatus(ErrorTypes::ErrorType::MUST_BE, ']'); // TODO: Multiple MUST_BE characters.
	case State::LOWER:
		if (c == ',' && depth_ == 0)
		{
			Status status = child_parser->Finalize();
			if (status.Failed()) {
				return PartialStatus(status);
			}

			unique_ptr<ExpTree> tree = child_parser->GetTree();
			if (tree == nullptr) {
				return PartialStatus(ErrorTypes::ErrorType::UNKNOWN);
			}
			node->SetLowerBound(tree->GetRoot());
			state_ = State::UPPER;
			child_parser = make_unique<InternalParser>();
			return PartialStatus();
		}
		else {
			if (c == '{')
			{
				depth_++;
			} else if (c == '}')
			{
				depth_--;
			}
			Status result = child_parser->ParseNextChar(c);
			return PartialStatus(result);
		}
	case State::UPPER:
		if (c == ']' && depth_ == 0)
		{
			Status status = child_parser->Finalize();
			if (status.Failed()) {
				return PartialStatus(status);
			}

			unique_ptr<ExpTree> tree = child_parser->GetTree();
			if (tree == nullptr) {
				return PartialStatus(ErrorTypes::ErrorType::UNKNOWN);
			}
			node->SetUpperBound(tree->GetRoot());
			state_ = State::OPEN_EXPRESSION;
			child_parser = make_unique<InternalParser>();
			return PartialStatus();
		}
		else {
			if (c == '{')
			{
				depth_++;
			}
			else if (c == '}')
			{
				depth_--;
			}
			Status result = child_parser->ParseNextChar(c);
			return PartialStatus(result);
		}
	case State::OPEN_EXPRESSION:
		state_ = State::EXPRESSION;
		if (c != '{') {
			return PartialStatus(ErrorTypes::ErrorType::MUST_BE, '{');
		}
		return PartialStatus();
	case State::EXPRESSION: {
		if (c == '}' && depth_ == 0) {
			Status status = child_parser->Finalize();
			if (status.Failed()) {
				return PartialStatus(status);
			}

			unique_ptr<ExpTree> tree = child_parser->GetTree();
			if (tree == nullptr) {
				return PartialStatus(ErrorTypes::ErrorType::UNKNOWN);
			}
			node->AddChild(tree->GetRoot());
			state_ = State::DONE;
			outputNode = move(node);
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
	case State::DONE:
		return PartialStatus(ErrorTypes::ErrorType::UNKNOWN);
	}
}