#pragma once

#include <cctype>
#include <iostream>
#include <stdio.h>
#include <string>

#include "InternalParser.h"

InternalParser::InternalParser() :
	state_(State::BEGIN),
	tree_(make_unique<ExpTree>()),
	last_oper((Operator)-1),
	parenthesis_depth(0),
	position_(-1),
	input_("") { }

int InternalParser::ParseString(const string& equation) {
	// Parse each character and count position
	for (char c : equation) {
		if (!ParseNextChar(c)) {
			input_ = equation;
			return position_;
		}
	}
	return -1;
}

bool InternalParser::ParseNextChar(const char c) {
	input_ += c;
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
			state_ = State::CANNOT_PROCEED;
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
		state_ = State::UNPAIRED_PARENTHESIS;
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
		state_ = State::UNKNOWN_ERROR;
		return;
	}
}

string InternalParser::PrintProgress(const IPrinter &printer) const {
	string progress;
	if (tree_->PeekRoot() != nullptr) {
		progress = tree_->Print(printer);
	}

	if ((int)last_oper != -1) {
		progress += printer.PrintOperatorPrefix(last_oper);
	}

	if (active_func_parser != nullptr) {
		progress += active_func_parser->PrintProgress(printer);
	}

	progress += cache_;
	return progress;
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
	case State::UOPER:
	case State::NOPER:
	case State::INT:
	case State::FLOAT:
		cache_ += c;
		state_ = State::INT;
		return true;
	default:
		state_ = State::CANNOT_PROCEED;
		return false;
	}
}

bool InternalParser::ParseLetter(const char c) {
	switch (state_)
	{
	case State::BEGIN:
	case State::UOPER:
	case State::NOPER:
		tree_->AddNode(make_unique<VarValueNode>(c));
		state_ = State::VARIABLE;
		last_oper = (Operator)-1;
		return true;
	case State::INT:
	case State::FLOAT:
		CompleteValue();
	case State::VALUE:
	case State::VARIABLE:
		tree_->AddNode(make_unique<NOperNode>('*'));
		tree_->AddNode(make_unique<VarValueNode>(c));
		state_ = State::VARIABLE;
		last_oper = (Operator)-1;
		return true;
	default:
		state_ = State::CANNOT_PROCEED;
		return false;
	}
}

bool InternalParser::ParseOper(const char c) {
	switch (state_)
	{
	case State::BEGIN:
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
		auto tempNode = make_unique<BOperNode>(c);
		last_oper = tempNode->GetOperator();
		tree_->AddNode(move(tempNode));
	}
	else {
		auto tempNode = make_unique<NOperNode>(c);
		last_oper = tempNode->GetOperator();
		tree_->AddNode(move(tempNode));
	}
	state_ = State::NOPER;
	if (c == '-' || c == '/') {
		auto tempNode = make_unique<UOperNode>(c);
		last_oper = tempNode->GetOperator();
		tree_->AddNode(move(tempNode));
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
	{
		auto tempNode = make_unique<UOperNode>(c);
		last_oper = tempNode->GetOperator();
		tree_->AddNode(move(tempNode));
		state_ = State::UOPER;
		return true;
	}
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
	case State::BEGIN:
	case State::UOPER:
	case State::NOPER: {
		if (c == '(') {
			tree_->AddNode(make_unique<UOperNode>(c));
			parenthesis_depth++;
			state_ = State::BEGIN;
			last_oper = Operator::UNRESOLVED_PARENTHESIS;
		}
		else if (c == ')') {
			// TODO: Check parenthesis depth
			parenthesis_depth--;
			tree_->CloseParenthesis();
			state_ = State::VALUE;
			last_oper = Operator(-1);
		}
		else if (c == '<') {
			active_func_parser = MakeFuncParser(Operator::VECTOR);
			active_func_parser->ParseFirstChar(c);
			state_ = State::FUNCTION;
		}
		else {
			state_ = State::CANNOT_PROCEED;
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
		state_ = State::ALREADY_FLOAT;
		return false;
	case State::BEGIN:
		state_ = State::CANNOT_BEGIN;
		return false;
	default:
		state_ = State::CANNOT_PROCEED;
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
		cache_ = "";
		state_ = State::PARTIAL_FUNCTION;
		return true;
	case State::PARTIAL_FUNCTION:
		// TODO: handle new line
		state_ = State::CANNOT_PROCEED;
		return false;
	default:
		state_ = State::CANNOT_PROCEED;
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
		state_ = State::INVALID_FUNCTION;
		return false;
	}
}

bool InternalParser::ParseFunction(const char c) {
	unique_ptr<BranchNode> node;
	bool status = active_func_parser->ParseNextChar(c, node);
	if (node != nullptr) {
		tree_->AddNode(move(node));
		state_ = State::VALUE;
		last_oper = (Operator)-1;
		delete active_func_parser;
		active_func_parser = nullptr;
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

IFuncParser *MakeFuncParser(const Operator oper) {
	switch (oper)
	{
	case Operator::SINE:
	case Operator::COSINE:
	case Operator::TANGENT:
	case Operator::COSECANT:
	case Operator::SECANT:
	case Operator::COTANGENT:
		return new SinusoidalFuncParser(oper);
	case Operator::DERIVATIVE:
		return new DiffFuncParser();
	case Operator::VECTOR:
		return new VectorParser();
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
