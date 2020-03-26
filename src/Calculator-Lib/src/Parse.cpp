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
#include "../include/VarValueNode.h"
#include "../include/UOperNode.h"

using namespace std;

ParseState::ParseState() : state_(ParserState::BEGIN), tree_(make_unique<ExpTree>()), parenthesis_depth(0) { }

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
		case ParserState::BEGIN:
			return ParseBegin(c);
		case ParserState::NOPER:
			return ParseNOper(c);
		case ParserState::UOPER:
			return ParseUOper(c);
		case ParserState::INT:
			return ParseInt(c);
		case ParserState::FLOAT:
			return ParseFloat(c);
		case ParserState::VARABLE:
			return ParseVar(c);
		case ParserState::CLOSED_PARENTHESIS:
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
		case ParserState::INT:
			CompleteInt();
			break;
		case ParserState::FLOAT:
			CompleteFloat();
			break;
		default:
			break;
	}
	state_ = ParserState::DONE;
}

/// <summary>
/// Get ExpTree from parser
/// </summary>
/// <returns>The ExpTree or nullptr if incomplete</returns>
unique_ptr<ExpTree> ParseState::GetTree() {
	if (state_ != ParserState::DONE) {
		return nullptr;
	}

	state_ = ParserState::BEGIN;
	unique_ptr<ExpTree> result = move(tree_);
	tree_ = make_unique<ExpTree>();
	return result;
}

/// <summary>
/// Add final ValueNode and return ExpTree
/// </summary>
/// <returns>The parsed expression tree, or nullptr if invalid</returns>
unique_ptr<ExpTree> ParseState::FinalizeAndReturn() {
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
		state_ = ParserState::INT;
		return true;
	}
	else if (islower(c)) {
		tree_->AddNode(make_unique<VarValueNode>(c));
		state_ = ParserState::VARABLE;
		return true;
	}
	else {
		switch(c) {
			// Unary +
			case '+':
			// Unary -
			case '-':
				tree_->AddNode(make_unique<UOperNode>(c));
				state_ = ParserState::UOPER;
				return true;
			case '(':
				tree_->AddNode(make_unique<UOperNode>(c));
				parenthesis_depth++;
				state_ = ParserState::BEGIN;
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
		state_ = ParserState::INT;
		return true;
	}
	else if (islower(c)) {
		tree_->AddNode(make_unique<VarValueNode>(c));
		state_ = ParserState::VARABLE;
		return true;
	}
	else {
		switch (c) {
			case '+':
			case '-':
				tree_->AddNode(make_unique<UOperNode>(c));
				state_ = ParserState::UOPER;
				return true;
			case '(':
				tree_->AddNode(make_unique<UOperNode>(c));
				parenthesis_depth++;
				state_ = ParserState::BEGIN;
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
		// Saves int progress and declares INT state
		numProgress_ = c;
		state_ = ParserState::INT;
		return true;
	}
	else if (islower(c)) {
		tree_->AddNode(make_unique<NOperNode>('*'));
		tree_->AddNode(make_unique<VarValueNode>(c));
		state_ = ParserState::VARABLE;
		return true;
	}
	else {
		switch (c)
		{
			case '+':
			case '-':
				tree_->AddNode(make_unique<UOperNode>(c));
				state_ = ParserState::UOPER;
				return true;
			case '(':
				tree_->AddNode(make_unique<UOperNode>(c));
				parenthesis_depth++;
				state_ = ParserState::BEGIN;
				return true;
		}
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

		// Adds to int progress
		numProgress_.push_back(c);
		return true;	

	} 
	else if (islower(c)) {
		CompleteInt();
		tree_->AddNode(make_unique<NOperNode>('*'));
		tree_->AddNode(make_unique<VarValueNode>(c));
		state_ = ParserState::VARABLE;
		return true;
	} 
	else {
		switch (c) {
			case '+':
			case '*':
				CompleteInt();
				tree_->AddNode(make_unique<NOperNode>(c));
				state_ = ParserState::NOPER;
				return true;
			case '-':
				CompleteInt();
				// Makes addition operator and adds a unary minus
				tree_->AddNode(make_unique<NOperNode>('+'));
				tree_->AddNode(make_unique<UOperNode>('-'));
				state_ = ParserState::UOPER;
				return true;
			case '^':
				CompleteInt();
				tree_->AddNode(make_unique<BOperNode>(c));
				return true;
			case'(':
				CompleteInt();
				// Adds implied multiply then parenthesis
				tree_->AddNode(make_unique<NOperNode>('*'));
				tree_->AddNode(make_unique<UOperNode>(c));
				parenthesis_depth++;
				state_ = ParserState::BEGIN;
				return true;
			case ')':
				CompleteInt();
				parenthesis_depth--;
				if (parenthesis_depth < 0) {
					// No parenthesis to be closed
					return false;
				}
				tree_->CloseParenthesis();
				state_ = ParserState::CLOSED_PARENTHESIS;
				return true;
			case '.':
				numProgress_.push_back(c);
				state_ = ParserState::FLOAT;
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
	else if (islower(c)) {
		CompleteFloat();
		tree_->AddNode(make_unique<NOperNode>('*'));
		tree_->AddNode(make_unique<VarValueNode>(c));
		state_ = ParserState::VARABLE;
		return true;
	}
	else {
		switch (c) {
			case '+':
			case '*':
				CompleteFloat();
				tree_->AddNode(make_unique<NOperNode>(c));
				state_ = ParserState::NOPER;
				return true;
			case '-':
				CompleteFloat();
				// Add addition operator then unary minus
				tree_->AddNode(make_unique<NOperNode>(c));
				tree_->AddNode(make_unique<UOperNode>('-'));
				state_ = ParserState::UOPER;
				return true;
			case '^':
				CompleteFloat();
				tree_->AddNode(make_unique<BOperNode>('^'));
				state_ = ParserState::NOPER;
				return true;
			case ')':
				CompleteFloat();
				parenthesis_depth--;
				if (parenthesis_depth < 0) {
					// No parenthesis to be closed
					return false;
				}
				tree_->CloseParenthesis();
				state_ = ParserState::CLOSED_PARENTHESIS;
				return true;
		}
	}
	return false;
}

/// <summary>
/// Parse the next character from the VARIABLE state
/// </summary>
/// <param name="c">Character to parse</param>
/// <returns>false if the character can't work after VARIABLE</returns>
bool ParseState::ParseVar(char c) {
	if (islower(c)) {
		tree_->AddNode(make_unique<NOperNode>('*'));
		tree_->AddNode(make_unique<VarValueNode>(c));
		state_ = ParserState::VARABLE;
		return true;
	}
	else {
		switch (c) {
			case '+':
			case '*':
				tree_->AddNode(make_unique<NOperNode>(c));
				state_ = ParserState::NOPER;
				return true;
			case '-':
				// Add addition operator then unary minus
				tree_->AddNode(make_unique<NOperNode>(c));
				tree_->AddNode(make_unique<UOperNode>('-'));
				state_ = ParserState::UOPER;
				return true;
			case '^':
				tree_->AddNode(make_unique<BOperNode>('^'));
				state_ = ParserState::NOPER;
				return true;
			case '(':
				tree_->AddNode(make_unique<NOperNode>('*'));
				tree_->AddNode(make_unique<UOperNode>(c));
				state_ = ParserState::BEGIN;
				parenthesis_depth++;
				return true;
			case ')':
				parenthesis_depth--;
				if (parenthesis_depth < 0) {
					// No parenthesis to be closed
					return false;
				}
				tree_->CloseParenthesis();
				state_ = ParserState::CLOSED_PARENTHESIS;
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
		// Adds implied multiply
		tree_->AddNode(make_unique<NOperNode>('*'));

		// Saves int progress and declares INT state
		numProgress_ = c;
		state_ = ParserState::INT;
		return true;
	}
	else {
		unique_ptr<NOperNode> node = make_unique<NOperNode>(c);
		switch (c) {
			case '+':
			case '*':
				tree_->AddNode(move(node));
				state_ = ParserState::NOPER;
				return true;
			case '-':
				// Makes addition operator and adds a unary minus
				tree_->AddNode(make_unique<NOperNode>(c));
				tree_->AddNode(make_unique<UOperNode>('-'));
				state_ = ParserState::UOPER;
				return true;
			case '^':
				tree_->AddNode(make_unique<BOperNode>(c));
				state_ = ParserState::NOPER;
				return true;
			case '(':
				tree_->AddNode(make_unique<NOperNode>('*'));
				tree_->AddNode(make_unique<UOperNode>(c));
				parenthesis_depth++;
				state_ = ParserState::BEGIN;
				return true;
			case ')':
				parenthesis_depth--;
				if (parenthesis_depth < 0) {
					// No parenthesis to be closed
					return false;
				}
				tree_->CloseParenthesis();
				state_ = ParserState::CLOSED_PARENTHESIS;
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
	
	tree_->AddNode(MakeValueNode(value));
	
	numProgress_ = "";	
}

/// <summary>
/// Finished building a float and add to the tree
/// </summary>
void ParseState::CompleteFloat() {
	float value = stof(numProgress_);

	tree_->AddNode(MakeValueNode(value));

	numProgress_ = "";
}

/// <summary>
/// Get an ExpTree from an equation string
/// </summary>
/// <param name="c">Character to parse</param>
/// <returns>false if the character can't work in BEGIN</returns>
unique_ptr<ExpTree> Parse(const string& equation)
{
	ParseState state;
	state.ParseString(equation);

	return state.FinalizeAndReturn();
}
