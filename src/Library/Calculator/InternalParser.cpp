#pragma once

#include <cctype>
#include <iostream>
#include <stdio.h>
#include <string>

#include "InternalParser.h"

#include "Helper.h"

InternalParser::InternalParser() :
	state_(State::BEGIN),
	tree_(make_unique<ExpTree>()),
	parenthesis_depth(0),
	position_(-1),
	input_("") {
}

Status InternalParser::ParseString(const string& equation) {
	input_ = equation;
	// Parse each character and count position
	for (char c : equation) {
		Status status = ParseNextChar(c, true);
		if (status.Failed()) {
			return status;
		}
	}

	return Status(input_, position_);
}

Status InternalParser::ParseNextChar(const char c, bool hasFullString) {
	if (!hasFullString) {
		input_ += c;
	}
	position_++;

	if (isspace(c)) {
		return Status(input_, position_);
	}

	if (state_ == State::FUNCTION) {
		return ParseFunction(c);
	}
	else if (state_ == State::PARTIAL_FUNCTION) {
		return ParsePartialFunc(c);
	}
	else if (isdigit(c)) {
		return ParseDigit(c);
	}
	else if (isalpha(c)) {
		return ParseLetter(c);
	}
	else {
		switch (c)
		{
		case '[':
		case '{':
		case '(':
		case '<':
		case '>':
		case ')':
		case '}':
		case ']':
			return ParseBracket(c);
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			return ParseOper(c);
		case '.':
			return ParseDecimal();
		case '\\':
			return ParseEscape();
		default:
			return EnterErrorState(ErrorTypes::ErrorType::CANNOT_PROCEED);
		}
	}
}

Status InternalParser::Finalize() {
	if (state_ >= State::DONE) {
		return Status(input_, position_);
	}

	CompleteValue();

	if (parenthesis_depth != 0) {
		return EnterErrorState(ErrorTypes::ErrorType::UNPAIRED_PARENTHESIS);
	}

	switch (state_)
	{
	case State::INT:
	case State::FLOAT:
	case State::VARIABLE:
	case State::VALUE:
		state_ = State::DONE;
		return Status(input_, position_);

	default:
		return EnterErrorState(ErrorTypes::ErrorType::UNKNOWN);
	}
}

Status InternalParser::Finalize(unique_ptr<ExpTree>* tree) {
	if (state_ >= State::DONE) {
		return Status(input_, position_);
	}

	CompleteValue();

	if (parenthesis_depth != 0) {
		return EnterErrorState(ErrorTypes::ErrorType::UNPAIRED_PARENTHESIS);
	}

	switch (state_)
	{
	case State::INT:
	case State::FLOAT:
	case State::VARIABLE:
	case State::VALUE:
		state_ = State::DONE;
		*tree = GetTree();
		return Status(input_, position_);

	default:
		return EnterErrorState(ErrorTypes::ErrorType::UNKNOWN);
	}
}

unique_ptr<ExpTree> InternalParser::GetTree() {
	if (state_ != State::DONE) {
		return nullptr;
	}

	state_ = State::DONE;
	unique_ptr<ExpTree> result = move(tree_);
	tree_ = make_unique<ExpTree>();
	return result;
}

bool InternalParser::IsDone() const {
	return state_ >= State::DONE;
}

Status InternalParser::ParseDigit(const char c) {
	switch (state_)
	{
	case State::VALUE:
		tree_->AddNode(make_unique<NOperNode>('*'));
	case State::BEGIN:
	case State::OPEN_PARENTHESIS:
	case State::UOPER:
	case State::NOPER:
	case State::INT:
		state_ = State::INT;
	case State::FLOAT:
		cache_ += c;
		return Status(input_, position_);
	default:
		return EnterErrorState(ErrorTypes::ErrorType::CANNOT_PROCEED);
	}
}

Status InternalParser::ParseLetter(const char c) {
	switch (state_)
	{
	case State::BEGIN:
	case State::OPEN_PARENTHESIS:
	case State::UOPER:
	case State::NOPER:
		tree_->AddNode(make_unique<VarValueNode>(c));
		state_ = State::VARIABLE;
		return Status(input_, position_);
	case State::INT:
	case State::FLOAT:
		CompleteValue();
	case State::VALUE:
	case State::VARIABLE:
		tree_->AddNode(make_unique<NOperNode>('*'));
		tree_->AddNode(make_unique<VarValueNode>(c));
		state_ = State::VARIABLE;
		return Status(input_, position_);
	default:
		return EnterErrorState(ErrorTypes::ErrorType::CANNOT_PROCEED);
	}
}

Status InternalParser::ParseOper(const char c) {
	switch (state_)
	{
	case State::BEGIN:
	case State::OPEN_PARENTHESIS:
	case State::NOPER:
		return ParseUOper(c);
	case State::INT:
	case State::FLOAT:
	case State::VALUE:
	case State::VARIABLE:
		CompleteValue();
		return ParseNOper(c);
	default:
		return EnterErrorState(ErrorTypes::ErrorType::CANNOT_PROCEED);
	}
}

Status InternalParser::ParseNOper(const char c) {
	// Appropiate state guarenteed
	if (c == '^') {
		tree_->AddNode(make_unique<BOperNode>(c));
	}
	else {
		tree_->AddNode(make_unique<NOperNode>(c));
	}
	state_ = State::NOPER;
	if (c == '-' || c == '/') {
		tree_->AddNode(make_unique<UOperNode>(c));
		state_ = State::UOPER;
	}
	return Status(input_, position_);
}

Status InternalParser::ParseUOper(const char c) {
	// Appropiate state guarenteed
	switch (c)
	{
	case '+':
	case '-':
		tree_->AddNode(make_unique<UOperNode>(c));
		state_ = State::UOPER;
		return Status(input_, position_);
	default:
		return EnterErrorState(ErrorTypes::ErrorType::CANNOT_PROCEED);
	}
}

Status InternalParser::ParseBracket(const char c) {
	switch (state_)
	{
	case State::INT:
	case State::FLOAT:
		CompleteValue();
	case State::VALUE:
	case State::VARIABLE:
		tree_->AddNode(make_unique<NOperNode>('*'));
	case State::UOPER:
	case State::NOPER:
	case State::BEGIN:
	case State::OPEN_PARENTHESIS:
	 {
		if (c == '(') {
			tree_->AddNode(make_unique<UOperNode>(c));
			parenthesis_depth++;
			state_ = State::OPEN_PARENTHESIS;
		}
		else if (c == ')') {
			if (parenthesis_depth == 0) {
				return EnterErrorState(ErrorTypes::ErrorType::UNPAIRED_PARENTHESIS);
			}
			else if (state_ == State::OPEN_PARENTHESIS) {
				return EnterErrorState(ErrorTypes::ErrorType::CANNOT_PROCEED);
			}

			parenthesis_depth--;
			tree_->CloseParenthesis();
			state_ = State::VALUE;
		}
		else if (c == '<') {
			active_func_parser = MakeFuncParser(Operator::TENSOR);
			active_func_parser->ParseFirstChar(c);
			state_ = State::FUNCTION;
		}
		else {
			return EnterErrorState(ErrorTypes::ErrorType::UNPAIRED_PARENTHESIS);
		}
		return Status(input_, position_);
	}
	}
}

Status InternalParser::ParseDecimal() {
	switch (state_)
	{
	case State::INT:
		cache_ += '.';
		state_ = State::FLOAT;
		return Status(input_, position_);
	case State::FLOAT:
		return EnterErrorState(ErrorTypes::ErrorType::ALREADY_FLOAT);
	case State::BEGIN:
		return EnterErrorState(ErrorTypes::ErrorType::CANNOT_BEGIN);
	default:
		return EnterErrorState(ErrorTypes::ErrorType::CANNOT_PROCEED);
	}
}

Status InternalParser::ParseEscape() {
	switch (state_)
	{
	case State::INT:
	case State::FLOAT:
		CompleteValue();
	case State::VALUE:
	case State::VARIABLE:
		tree_->AddNode(make_unique<NOperNode>('*'));
	case State::NOPER:
	case State::UOPER:
	case State::BEGIN:
	case State::OPEN_PARENTHESIS:
		cache_ = "";
		state_ = State::PARTIAL_FUNCTION;
		return Status(input_, position_);
	case State::PARTIAL_FUNCTION:
		// TODO: handle new line
		return EnterErrorState(ErrorTypes::ErrorType::CANNOT_PROCEED);
	default:
		return EnterErrorState(ErrorTypes::ErrorType::CANNOT_PROCEED);
	}
}

Status InternalParser::ParsePartialFunc(const char c) {
	if (isalpha(c)) {
		cache_ += c;
		return Status(input_, position_);
	}
	else if (operator_map.find(cache_) != operator_map.end()) {
		Operator oper = operator_map.at(cache_);
		active_func_parser = MakeFuncParser(oper);
		state_ = State::FUNCTION;
		cache_ = "";
		PartialStatus status = active_func_parser->ParseFirstChar(c);
		return Status(status, input_, position_);
	}
	else {
		return EnterErrorState(ErrorTypes::ErrorType::INVALID_FUNCTION);
	}
}

Status InternalParser::ParseFunction(const char c) {
	unique_ptr<BranchNode> node;
	PartialStatus status = active_func_parser->ParseNextChar(c, node);
	if (node != nullptr) {
		tree_->AddNode(move(node));
		state_ = State::VALUE;
	}
	return Status(status, input_, position_);
}

void InternalParser::CompleteValue() {
	if (state_ != State::INT && state_ != State::FLOAT) {
		return;
	}

	float value = stof(cache_);
	tree_->AddNode(MakeValueNode(value));
	cache_ = "";
}

Status InternalParser::EnterErrorState(ErrorTypes::ErrorType errorType, char expectedChar) {
	state_ = State::ERROR;
	return Status(errorType, input_, position_, expectedChar);
}

unique_ptr<IFuncParser> MakeFuncParser(const Operator oper) {
	switch (oper)
	{
	case Operator::SINE:
	case Operator::COSINE:
	case Operator::TANGENT:
	case Operator::COSECANT:
	case Operator::SECANT:
	case Operator::COTANGENT:
		return unique_ptr<IFuncParser>(new SinusoidalFuncParser(oper));
	case Operator::DERIVATIVE:
		return unique_ptr<IFuncParser>(new DiffFuncParser());
	case Operator::INTEGRAL:
		return unique_ptr<IFuncParser>(new IntegralFuncParser());
	case Operator::TENSOR:
		return unique_ptr<IFuncParser>(new VectorParser());
	}
}

Status Parse(const string& equation, unique_ptr<ExpTree>* tree)
{
	InternalParser state;
	Status result = state.ParseString(equation);
	while (!state.IsDone())
	{
		if (!result.Failed()) {
			result = state.Finalize(tree);
		}
		else {
			*tree = nullptr;
			return result;
		}
	}
	return result;
}
