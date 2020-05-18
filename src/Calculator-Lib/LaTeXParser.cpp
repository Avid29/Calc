#pragma once

#include <cctype>
#include <iostream>
#include <stdio.h>
#include <string>

#include "LaTeXParser.h"
#include "NOperNode.h"
#include "UOperNode.h"
#include "VarValueNode.h"

LaTeXParser::LaTeXParser() :
	state_(State::BEGIN),
	tree_(make_unique<ExpTree>()),
	parenthesis_depth(0),
	position_(-1),
	input_("") { }

int LaTeXParser::ParseString(const string& equation) {
	// Parse each character and count position
	for (char c : equation) {
		if (!ParseNextChar(c)) {
			input_ = equation;
			return position_;
		}
	}
}

bool LaTeXParser::ParseNextChar(const char c) {
	input_ += c;
	position_++;

	if (isdigit(c)) {
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
			return ParseOper(c);
		case '^':
		case '_':
		case '\\':
			return ParseSpecial(c);
		default:
			state_ = State::CANNOT_PROCEED;
			return false;
		}
	}
}

void LaTeXParser::Finalize() {
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

unique_ptr<ExpTree> LaTeXParser::GetTree() {
	if (state_ != State::DONE) {
		return nullptr;
	}

	state_ = State::BEGIN;
	unique_ptr<ExpTree> result = move(tree_);
	tree_ = make_unique<ExpTree>();
	return result;
}

unique_ptr<ExpTree> LaTeXParser::FinalizeAndReturn() {
	Finalize();
	return GetTree();
}

bool LaTeXParser::IsDone() const {
	return state_ == State::DONE;
}

bool LaTeXParser::ParseDigit(const char c) {
	switch (state_)
	{
	case State::BEGIN:
	case State::UOPER:
	case State::NOPER:
	case State::INT:
	case State::FLOAT:
		cache_ += c;
		state_ = State::INT;
		return true;
	case State::PARTIAL_FUNCTION:
		cache_ += c;
		return true;
	default:
		state_ = State::CANNOT_PROCEED;
		return false;
	}
}

bool LaTeXParser::ParseLetter(const char c) {
	switch (state_)
	{
	case State::BEGIN:
	case State::UOPER:
	case State::NOPER:
		tree_->AddNode(make_unique<VarValueNode>(c));
		state_ = State::VARIABLE;
		return true;
	case State::VALUE:
	case State::VARIABLE:
		tree_->AddNode(make_unique<NOperNode>('*'));
		tree_->AddNode(make_unique<VarValueNode>(c));
		return true;
	default:
		state_ = State::CANNOT_PROCEED;
		return false;
	}
}

bool LaTeXParser::ParseOper(const char c) {
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

bool LaTeXParser::ParseNOper(const char c) {
	// Appropiate state guarenteed
	tree_->AddNode(make_unique<NOperNode>(c));
	state_ = State::NOPER;
	if (c == '-' || c == '/') {
		tree_->AddNode(make_unique<UOperNode>(c));
		state_ = State::UOPER;
	}
	return true;
}

bool LaTeXParser::ParseUOper(const char c) {
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

bool LaTeXParser::ParseBracket(const char c) {
	if (c == '}') {
		switch (state_)
		{
		case State::VALUE:
		case State::VARIABLE:
		case State::INT:
		case State::FLOAT: {
			if (tree_stack.size() == 0) {
				state_ = State::GENERIC_ERROR;
				return false;
			}
			unique_ptr<ExpNode> node = tree_->GetRoot();
			tree_ = move(tree_stack.top());
			tree_stack.pop();
			tree_->AddAnyNode(move(node));
		}
			return true;
		default:
			state_ = State::CANNOT_PROCEED;
			return false;
		}
	}

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
		}
		else if (c == ')') {
			// TODO: Check parenthesis depth
			parenthesis_depth--;
			tree_->CloseParenthesis();
			state_ = State::VALUE;
		}
		else {
			state_ = State::CANNOT_PROCEED;
			return false;
		}
		return true;
	}
	case State::PARTIAL_FUNCTION: {
		if (c == '{') {
			tree_stack.push(move(tree_));
			tree_ = make_unique<ExpTree>();
			state_ = State::BEGIN;
		}
		return true;
	}
	}
}

bool LaTeXParser::ParseSpecial(const char c) {
	return false;
}

void LaTeXParser::CompleteValue() {
	if (state_ != State::INT && state_ != State::FLOAT) {
		return;
	}

	float value = stof(cache_);
	tree_->AddNode(MakeValueNode(value));
	cache_ = "";
}
