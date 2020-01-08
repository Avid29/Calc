#pragma once
#include <string>
#include <vector>

#include "ExpNode.h"
#include "ExpTree.h"
#include "FValueNode.h"
#include "IValueNode.h"
#include "OperNode.h"
#include "ValueNode.h"

using namespace std;

// The parse state is based on the previous character the parser saw
enum ParserState {
	BEGIN,
	// Nary (or binary) Operator
	NOPER,
	// Unary Operator
	UOPER,
	INT,
	FLOAT, // Or decimal
	DONE // Finalized() ran
};

class ParseState {
	public:

		ParseState();

		/// <summary>
		/// Parse a string into a tree
		/// </summary>
		/// <param name="equation">string to parse</param>
		/// <returns>-1 on success, or the invalid character's position</returns>
		int ParseString(const string& equation);
		

		/// <summary>
		/// Parse the next character into the tree
		/// </summary>
		/// <param name="c">Character to parse</param>
		/// <returns>false if the character can't work in that position</returns>
		bool ParseNextChar(char c);

		/// <summary>
		/// Add the final ValueNode to the tree
		/// </summary>
		void Finalize();


		/// <summary>
		/// Get ExpTree from parser
		/// </summary>
		/// <returns>The ExpTree or nullptr if incomplete</returns>
		ExpTree *GetTree();

		/// <summary>
		/// Add final ValueNode and return ExpTree
		/// </summary>
		/// <returns>The parsed expression tree, or nullptr if invalid</returns>
		ExpTree *FinalizeAndReturn();

	private:

		/// <summary>
		/// Parse the next character from the BEGIN state
		/// </summary>
		/// <param name="c">Character to parse</param>
		/// <returns>false if the character can't work after BEGIN</returns>
		bool ParseBegin(char c);

		/// <summary>
		/// Parse the next character from the NOPER state
		/// </summary>
		/// <param name="c">Character to parse</param>
		/// <returns>false if the character can't work after NOPER</returns>
		bool ParseNOper(char c);

		/// <summary>
		/// Parse the next character from the UOPER state
		/// </summary>
		/// <param name="c">Character to parse</param>
		/// <returns>false if the character can't work after UOPER</returns>
		bool ParseUOper(char c);

		/// <summary>
		/// Parse the next character from the INT state
		/// </summary>
		/// <param name="c">Character to parse</param>
		/// <returns>false if the character can't work after INT</returns>
		bool ParseInt(char c);

		/// <summary>
		/// Parse the next character from the FLOAT state
		/// </summary>
		/// <param name="c">Character to parse</param>
		/// <returns>false if the character can't work after FLOAT</returns>
		bool ParseFloat(char c);

		/// <summary>
		/// Finish building an int and add to the tree
		/// </summary>
		void CompleteInt();

		/// <summary>
		/// Finished building a float and add to the tree
		/// </summary>
		void CompleteFloat();

		ParserState state_;
		ExpTree *tree_;
		string numProgress_;
};

/// <summary>
/// Get an ExpTree from an equation string
/// </summary>
/// <param name="c">Character to parse</param>
/// <returns>false if the character can't work in BEGIN</returns>
ExpTree *Parse(const string& equation);
