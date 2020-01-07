#include <cctype>
#include <iostream>
#include <stdio.h>
#include <string>

#include "../include/BOperNode.h"
#include "../include/ExpNode.h"
#include "../include/FValueNode.h"
#include "../include/IValueNode.h"
#include "../include/OperNode.h"
#include "../include/NOperNode.h"
#include "../include/Parse.h"
#include "../include/ValueNode.h"
#include "../include/UOperNode.h"

#define DEBUG

using namespace std;

ParseState::ParseState() : state_ (BEGIN), tree_ (new ExpTree()) { }

int ParseState::ParseString(string equation)
{
	int i = 0;
	for (char c : equation) {
		if (!ParseNextChar(c))
		{
			return i;
		}
		i++;
	}
	return -1;
}

bool ParseState::ParseNextChar(char c) {
	switch (state_) {
		case BEGIN:
			return ParseBegin(c);
		case NOPER:
			return ParseNOper(c);
		case UOPER:
			return ParseUOper(c);
		case INT:
			return ParseInt(c);
		case FLOAT:
			return ParseFloat(c);
		default:
			return false;	
	}
}

void ParseState::Finalize() {

	#ifdef DEBUG
		printf("\nFinalizing:\n");
	#endif

	switch (state_) {
		case INT:
			DepositIntCache();
			state_ = DONE;
			break;
		case FLOAT:
			DepositFloatCache();
			state_ = DONE;
			break;
		default:
			break;
	}
}

ExpTree *ParseState::GetTree() {
	if (state_ != DONE) {
		return nullptr;
	}
	return tree_;
}

ExpTree *ParseState::FinalizeAndReturn() {
	Finalize();
	return GetTree();
}

bool ParseState::ParseBegin(char c) {

	#ifdef DEBUG
		printf("\nParse '%c' at Beginning:\n", c);
	#endif

	if (isdigit(c)) {

		cache_ = c;
		state_ = INT;

		#ifdef DEBUG
			printf("\"%s\" is cache\n", cache_.c_str());
		#endif

		return true;
	} else {
		switch(c) {
			case '+':
				#ifdef DEBUG
					printf("'%c' is '+', unary plus", c);
				#endif

				// TODO: Add Node

				state_ = UOPER;
				return true;
			case '-':

				#ifdef DEBUG
					printf("'%c' is '-', unary minus", c);
				#endif

				// TODO: Add Node
				
				state_ = UOPER;
				return true;
			case '*':
			case '^':

				#ifdef DEBUG
					printf("'%c' is not valid for Beginning\n", c);
				#endif

				return false;
		}
	}

	return false;
}

bool ParseState::ParseNOper(char c) {

	#ifdef DEBUG
		printf("\nParse '%c' after NOper:\n", c);
	#endif

	if (isdigit(c)) {
		cache_ = c;
		state_ = INT;

		#ifdef DEBUG
			printf("\"%s\" is cache\n", cache_.c_str());
		#endif
		return true;
	} else {
		switch (c) {
			case '+':
			case '*':
			case '^':
				// TODO: Handle Nary operators
				return false;	
		}
	}
	return false;
}

bool ParseState::ParseUOper(char c) {
	
	#ifdef DEBUG
		printf("\nParse '%c' after Unary Op\n", c);
	#endif		
	
	if (isdigit(c)) {
		
		cache_ = c;
		state_ = INT;

		#ifdef DEBUG
			printf("\"%s\" is cache\n", cache_.c_str());
		#endif
	}
	return false;
}

bool ParseState::ParseInt(char c) {
	
	#ifdef DEBUG
		printf("\nParse '%c' after Int:\n", c);
	#endif
	
	if (isdigit(c)) {
		cache_.push_back(c);

		#ifdef DEBUG
			printf("\"%s\" is cache\n", cache_.c_str());
		#endif

		return true;	
	} else {		
		NOperNode *node = new NOperNode(c);
		switch (c) {
			case '+':
				DepositIntCache();
			
				#ifdef DEBUG
					printf("Add OperNode '%c'\n", c);
				#endif

				tree_->AddNode(node);
				
				state_ = NOPER;
				return true;
			case '*':
				DepositIntCache();

				// TODO: Add Node
				
				state_ = NOPER;
				return true;
		}
	}

	return false;
}

bool ParseState::ParseFloat(char c) {
	return false;
}

void ParseState::DepositIntCache() {
	int value = stoi(cache_);

	#ifdef DEBUG
		printf("Add ValueNode %d\n", value);
	#endif
	
	IValueNode *value_node = new IValueNode(value);
	
	tree_->AddNode(value_node);
	
	cache_ = "";	
}

void ParseState::DepositFloatCache() {
	float value = stof(cache_);

	#ifdef DEBUG
		printf("Add ValueNode %f\n", value);
	#endif

	// TODO: Add Node

	cache_ = "";
}

ExpTree *Parse(string equation)
{
	ParseState *state = new ParseState();
	state->ParseString(equation);

	return state->FinalizeAndReturn();
}
