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

using namespace std;

ParseState::ParseState() : state_ (BEGIN), tree_ (new ExpTree()) { }

/// <summary>
/// Parse a string into a tree
/// </summary>
/// <param name="equation">string to parse</param>
/// <returns>-1 on success, or the invalid character's position</returns>
int ParseState::ParseString(const string& equation)
{
	// Parse each character, but count position
	int i = 0;
	for (char c : equation) {
		if (!ParseNextChar(c))
		{
			return i;
		}
		i++;
	}

	// Success
	return -1;
}

/// <summary>
/// Parse the next character into the tree
/// </summary>
/// <param name="c">Character to parse</param>
/// <returns>false if the character can't work in that position</returns>
bool ParseState::ParseNextChar(char c) {
	// Split the parse operations into different functions based on current state
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
		case CLOSED_PARENTHESIS:
			return ParseClosedPar(c);
		default:
			return false;	
	}
}

/// <summary>
/// Add the final ValueNode to the tree
/// </summary>
void ParseState::Finalize() {

	switch (state_) {
		case INT:
			CompleteInt();
			break;
		case FLOAT:
			CompleteFloat();
			break;
		default:
			break;
	}
	state_ = DONE;
}

/// <summary>
/// Get ExpTree from parser
/// </summary>
/// <returns>The ExpTree or nullptr if incomplete</returns>
ExpTree *ParseState::GetTree() {
	if (state_ != DONE) {
		return nullptr;
	}
	return tree_;
}

/// <summary>
/// Add final ValueNode and return ExpTree
/// </summary>
/// <returns>The parsed expression tree, or nullptr if invalid</returns>
ExpTree *ParseState::FinalizeAndReturn() {
	Finalize();
	return GetTree();
}

/// <summary>
/// Parse the next character from the BEGIN state
/// </summary>
/// <param name="c">Character to parse</param>
/// <returns>false if the character can't work after BEGIN</returns>
bool ParseState::ParseBegin(char c) {
	if (isdigit(c)) {
		// Save int progress and declare INT state
		numProgress_ = c;
		state_ = INT;
		return true;
	} else {
		UOperNode* node = new UOperNode(c);
		switch(c) {
			// Unary +
			case '+':
				// TODO: Add Node
				state_ = UOPER;
				return true;
			// Unary -
			case '-':
				// TODO: Add Node
				state_ = UOPER;
				return true;
			case '(':
				tree_->AddNode(node);
				parenthesis_depth++;
				state_ = BEGIN;
				return true;

			case '*':
			case '^':
			case ')':
				return false;
		}
	}

	return false;
}

/// <summary>
/// Parse the next character from the NOPER state
/// </summary>
/// <param name="c">Character to parse</param>
/// <returns>false if the character can't work after NOPER</returns>
bool ParseState::ParseNOper(char c) {

	if (isdigit(c)) {
		// Save int progress and declare INT state
		numProgress_ = c;
		state_ = INT;
		return true;
	} else {
		UOperNode* node = new UOperNode(c);
		switch (c) {
			case '+':
			case '-':
				// TODO: Handle Unary operators
				return false;
			case '(':
				tree_->AddNode(node);
				parenthesis_depth++;
				state_ = BEGIN;
				return true;
		}
	}
	return false;
}

/// <summary>
/// Parse the next character from the UOPER state
/// </summary>
/// <param name="c">Character to parse</param>
/// <returns>false if the character can't work after UOPER</returns>
bool ParseState::ParseUOper(char c) {	
	
	if (isdigit(c)) {
		// Save int progress and declare INT state
		numProgress_ = c;
		state_ = INT;
	}
	return false;
}

/// <summary>
/// Parse the next character from the INT state
/// </summary>
/// <param name="c">Character to parse</param>
/// <returns>false if the character can't work after INT</returns>
bool ParseState::ParseInt(char c) {
	if (isdigit(c)) {

		// Add to int progress
		numProgress_.push_back(c);
		return true;	

	} else {
		NOperNode* node = new NOperNode(c);
		switch (c) {
			case '+':
			case '*':
				CompleteInt();
				tree_->AddNode(node);
				state_ = NOPER;
				return true;
			case ')':
				CompleteInt();
				parenthesis_depth--;
				if (parenthesis_depth < 0) {
					// No parenthesis to be closed
					return false;
				}
				tree_->FinishOverride();
				state_ = CLOSED_PARENTHESIS;
				return true;
			case '.':
				numProgress_.push_back(c);
				state_ = FLOAT;
				return true;
		}
	}

	return false;
}

/// <summary>
/// Parse the next character from the FLOAT state
/// </summary>
/// <param name="c">Character to parse</param>
/// <returns>false if the character can't work after FLOAT</returns>
bool ParseState::ParseFloat(char c) {
	if (isdigit(c)) {
		numProgress_.push_back(c);
		return true;
	}
	else {
		NOperNode* node = new NOperNode(c);
		switch (c) {
			case '+':
			case '*':
				CompleteFloat();
				tree_->AddNode(node);
				state_ = NOPER;
				return true;
			case ')':
				CompleteFloat();
				parenthesis_depth--;
				if (parenthesis_depth < 0) {
					// No parenthesis to be closed
					return false;
				}
				tree_->FinishOverride();
				state_ = CLOSED_PARENTHESIS;
				return true;
		}
	}
	return false;
}

/// <summary>
/// Parse the next character from the CLOSED_PARENTHESIS state
/// </summary>
/// <param name="c">Character to parse</param>
/// <returns>false if the character can't work after CLOSED_PARENTHESIS</returns>
bool ParseState::ParseClosedPar(char c) {
	if (isdigit(c)) {
		// TODO: Implied multiply
		return false;
	}
	else {
		NOperNode* node = new NOperNode(c);
		switch (c) {
			case '+':
			case '*':
				tree_->AddNode(node);
				state_ = NOPER;
				return true;
			case ')':
				parenthesis_depth--;
				if (parenthesis_depth < 0) {
					// No parenthesis to be closed
					return false;
				}
				tree_->FinishOverride();
				state_ = CLOSED_PARENTHESIS;
				return true;

		}
		return false;
	}
}

/// <summary>
/// Finish building an int and add to the tree
/// </summary>
void ParseState::CompleteInt() {
	int value = stoi(numProgress_);
	
	IValueNode *value_node = new IValueNode(value);
	
	tree_->AddNode(value_node);
	
	numProgress_ = "";	
}

/// <summary>
/// Finished building a float and add to the tree
/// </summary>
void ParseState::CompleteFloat() {
	float value = stof(numProgress_);

	FValueNode* value_node = new FValueNode(value);

	tree_->AddNode(value_node);

	numProgress_ = "";
}

/// <summary>
/// Get an ExpTree from an equation string
/// </summary>
/// <param name="c">Character to parse</param>
/// <returns>false if the character can't work in BEGIN</returns>
ExpTree *Parse(const string& equation)
{
	ParseState *state = new ParseState();
	state->ParseString(equation);

	return state->FinalizeAndReturn();
}
