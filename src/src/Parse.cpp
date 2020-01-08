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
		default:
			return false;	
	}
}

/// <summary>
/// Add the final ValueNode to the tree
/// </summary>
void ParseState::Finalize() {

	#ifdef DEBUG
		printf("\nFinalizing:\n");
	#endif

	switch (state_) {
		case INT:
			CompleteInt();
			state_ = DONE;
			break;
		case FLOAT:
			CompleteFloat();
			state_ = DONE;
			break;
		default:
			break;
	}
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

	#ifdef DEBUG
		printf("\nParse '%c' at Beginning:\n", c);
	#endif

	if (isdigit(c)) {
		// Save int progress and declare INT state
		numProgress_ = c;
		state_ = INT;

		#ifdef DEBUG
			printf("\"%s\" is cache\n", numProgress_.c_str());
		#endif

		return true;
	} else {
		switch(c) {
			// Unary +
			case '+':
				#ifdef DEBUG
					printf("'%c' is '+', unary plus", c);
				#endif

				// TODO: Add Node

				state_ = UOPER;
				return true;
			// Unary -
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

/// <summary>
/// Parse the next character from the NOPER state
/// </summary>
/// <param name="c">Character to parse</param>
/// <returns>false if the character can't work after NOPER</returns>
bool ParseState::ParseNOper(char c) {

	#ifdef DEBUG
		printf("\nParse '%c' after NOper:\n", c);
	#endif

	if (isdigit(c)) {
		// Save int progress and declare INT state
		numProgress_ = c;
		state_ = INT;

		#ifdef DEBUG
			printf("\"%s\" is cache\n", numProgress_.c_str());
		#endif
		return true;
	} else {
		switch (c) {
			case '+':
			case '*':
			case '^':
				// TODO: Handle Unary operators
				return false;	
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
	
	#ifdef DEBUG
		printf("\nParse '%c' after Unary Op\n", c);
	#endif		
	
	if (isdigit(c)) {
		// Save int progress and declare INT state
		numProgress_ = c;
		state_ = INT;

		#ifdef DEBUG
			printf("\"%s\" is cache\n", numProgress_.c_str());
		#endif
	}
	return false;
}

/// <summary>
/// Parse the next character from the INT state
/// </summary>
/// <param name="c">Character to parse</param>
/// <returns>false if the character can't work after INT</returns>
bool ParseState::ParseInt(char c) {
	
	#ifdef DEBUG
		printf("\nParse '%c' after Int:\n", c);
	#endif
	
	if (isdigit(c)) {
		// Add to int progress
		numProgress_.push_back(c);

		#ifdef DEBUG
			printf("\"%s\" is cache\n", numProgress_.c_str());
		#endif

		return true;	
	} else {		
		NOperNode *node = new NOperNode(c);
		switch (c) {
			case '+':
				CompleteInt();
			
				#ifdef DEBUG
					printf("Add OperNode '%c'\n", c);
				#endif

				tree_->AddNode(node);
				
				state_ = NOPER;
				return true;
			case '*':
				CompleteInt();

				#ifdef DEBUG
					printf("Add OperNode '%c'\n", c);
				#endif

				tree_->AddNode(node);
				
				state_ = NOPER;
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
	// TODO: Float state
	return false;
}

/// <summary>
/// Finish building an int and add to the tree
/// </summary>
void ParseState::CompleteInt() {
	int value = stoi(numProgress_);

	#ifdef DEBUG
		printf("Add ValueNode %d\n", value);
	#endif
	
	IValueNode *value_node = new IValueNode(value);
	
	tree_->AddNode(value_node);
	
	numProgress_ = "";	
}

/// <summary>
/// Finished building a float and add to the tree
/// </summary>
void ParseState::CompleteFloat() {
	float value = stof(numProgress_);

	#ifdef DEBUG
		printf("Add ValueNode %f\n", value);
	#endif

	// TODO: Add Node

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
