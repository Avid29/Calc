#pragma once

#include <cctype>
#include <iostream>
#include <stdio.h>
#include <string>

#include "InternalParser.h"

InternalParser::InternalParser() :
	state_(State::BEGIN),
	tree_(make_unique<ExpTree>()),
	parenthesis_depth(0),
	position_(-1),
	input_("") {
}

int InternalParser::ParseString(const string& equation) {
	input_ = equation;
	// Parse each character and count position
	for (char c : equation) {
		if (!ParseNextChar(c, true)) {
			return position_;
		}
	}
	return -1;
}

bool InternalParser::ParseNextChar(const char c, bool hasFullString) {
	if (!hasFullString) {
		input_ += c;
	}
	position_++;

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
			EnterErrorState(Error::ErrorType::CANNOT_PROCEED);
			return false;
		}
	}
}

void InternalParser::Finalize() {
	if (state_ >= State::DONE) {
		return;
	}
	CompleteValue();
	if (parenthesis_depth != 0) {
		EnterErrorState(Error::ErrorType::UNPAIRED_PARENTHESIS);
		position_ = -1;
		return;
	}

	switch (state_)
	{
	case State::INT:
	case State::FLOAT:
	case State::VARIABLE:
	case State::VALUE:
		state_ = State::DONE;
		return;

	default:
		EnterErrorState(Error::ErrorType::UNKNOWN);
		return;
	}
}

unique_ptr<ExpTree> InternalParser::GetTree() {
	if (state_ != State::DONE) {
		return nullptr;
	}

	state_ = State::BEGIN;
	unique_ptr<ExpTree> result = move(tree_);
	tree_ = make_unique<ExpTree>();
	return result;
}

Error InternalParser::GetError() const {
	return error_;
}

unique_ptr<ExpTree> InternalParser::FinalizeAndReturn() {
	Finalize();
	return GetTree();
}

bool InternalParser::IsDone() const {
	return state_ == State::DONE;
}

bool InternalParser::ParseDigit(const char c) {
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
		return true;
	default:
		EnterErrorState(Error::ErrorType::CANNOT_PROCEED);
		return false;
	}
}

bool InternalParser::ParseLetter(const char c) {
	switch (state_)
	{
	case State::BEGIN:
	case State::OPEN_PARENTHESIS:
	case State::UOPER:
	case State::NOPER:
		tree_->AddNode(make_unique<VarValueNode>(c));
		state_ = State::VARIABLE;
		return true;
	case State::INT:
	case State::FLOAT:
		CompleteValue();
	case State::VALUE:
	case State::VARIABLE:
		tree_->AddNode(make_unique<NOperNode>('*'));
		tree_->AddNode(make_unique<VarValueNode>(c));
		state_ = State::VARIABLE;
		return true;
	default:
		EnterErrorState(Error::ErrorType::CANNOT_PROCEED);
		return false;
	}
}

bool InternalParser::ParseOper(const char c) {
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
		return false;
	}
}

bool InternalParser::ParseNOper(const char c) {
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
	return true;
}

bool InternalParser::ParseUOper(const char c) {
	// Appropiate state guarenteed
	switch (c)
	{
	case '+':
	case '-':
		tree_->AddNode(make_unique<UOperNode>(c));
		state_ = State::UOPER;
		return true;
	default:
		return false;
	}
}

bool InternalParser::ParseBracket(const char c) {
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
				EnterErrorState(Error::ErrorType::UNPAIRED_PARENTHESIS);
				return false;
			}
			else if (state_ == State::OPEN_PARENTHESIS) {
				EnterErrorState(Error::ErrorType::CANNOT_PROCEED);
				return false;
			}

			parenthesis_depth--;
			tree_->CloseParenthesis();
			state_ = State::VALUE;
		}
		else if (c == '<') {
			active_func_parser = MakeFuncParser(Operator::Vector);
			active_func_parser->ParseFirstChar(c);
			state_ = State::FUNCTION;
		}
		else {
			EnterErrorState(Error::ErrorType::UNPAIRED_PARENTHESIS);
			return false;
		}
		return true;
	}
	}
}

bool InternalParser::ParseDecimal() {
	switch (state_)
	{
	case State::INT:
		cache_ += '.';
		state_ = State::FLOAT;
		return true;
	case State::FLOAT:
		EnterErrorState(Error::ErrorType::ALREADY_FLOAT);
		return false;
	case State::BEGIN:
		EnterErrorState(Error::ErrorType::CANNOT_BEGIN);
		return false;
	default:
		EnterErrorState(Error::ErrorType::CANNOT_PROCEED);
		return false;
	}
}

bool InternalParser::ParseEscape() {
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
		return true;
	case State::PARTIAL_FUNCTION:
		// TODO: handle new line
		EnterErrorState(Error::ErrorType::CANNOT_PROCEED);
		return false;
	default:
		EnterErrorState(Error::ErrorType::CANNOT_PROCEED);
		return false;
	}
}

bool InternalParser::ParsePartialFunc(const char c) {
	if (isalpha(c)) {
		cache_ += c;
		return true;
	}
	else if (operator_map.find(cache_) != operator_map.end()) {
		Operator oper = operator_map.at(cache_);
		active_func_parser = MakeFuncParser(oper);
		state_ = State::FUNCTION;
		cache_ = "";
		return active_func_parser->ParseFirstChar(c);
	}
	else {
		EnterErrorState(Error::ErrorType::INVALID_FUNCTION);
		return false;
	}
}

bool InternalParser::ParseFunction(const char c) {
	unique_ptr<BranchNode> node;
	bool status = active_func_parser->ParseNextChar(c, node);
	if (node != nullptr) {
		tree_->AddNode(move(node));
		state_ = State::VALUE;
	}
	else if (!status) {
		EnterErrorState(active_func_parser->GetError());
	}
	return status;
}

void InternalParser::CompleteValue() {
	if (state_ != State::INT && state_ != State::FLOAT) {
		return;
	}

	float value = stof(cache_);
	tree_->AddNode(MakeValueNode(value));
	cache_ = "";
}

void InternalParser::EnterErrorState(Error::ErrorType errorType) {
	state_ = State::ERROR;
	error_ = Error(errorType, input_, position_);
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
	case Operator::Vector:
		return unique_ptr<IFuncParser>(new VectorParser());
	}
}

int Parse(const string& equation, unique_ptr<ExpTree>& tree)
{
	InternalParser state;
	int result = state.ParseString(equation);
	if (result == -1) {
		tree = state.FinalizeAndReturn();
	}
	else {
		tree = nullptr;
	}
	return result;
}