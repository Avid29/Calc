#pragma once
#include <string>
#include <vector>
#include <map>

#include "ExpNode.h"
#include "ExpTree.h"
#include "FValueNode.h"
#include "IValueNode.h"
#include "OperNode.h"
#include "ValueNode.h"

using namespace std;

// The parse state is based on the previous character the parser saw
enum class ParserState {
	BEGIN,
	// Nary (or binary) Operator
	NOPER,
	// Unary Operator
	UOPER,
	INT,
	FLOAT, // Or decimal
	VARABLE,
	CLOSED_PARENTHESIS,
	DONE, // Finalized() ran

	// Errors
	UNKNOWN_ERROR,
	CANNOT_BEGIN,
	CANNOT_PROCEED,
	UNPAIRED_PARENTHESIS,
	ALREADY_FLOAT,
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
		/// Get ExpTree from parser
		/// </summary>
		/// <returns>The ExpTree or nullptr if incomplete</returns>
		unique_ptr<ExpTree> GetTree();

		/// <summary>
		/// Add the final ValueNode to the tree
		/// </summary>
		void Finalize();

		/// <summary>
		/// Add final ValueNode and return ExpTree
		/// </summary>
		/// <returns>The parsed expression tree, or nullptr if invalid</returns>
		unique_ptr<ExpTree> FinalizeAndReturn();

		// Prints the error if the parser is in error state
		void PrintError();

		bool IsDone() const;
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
		/// Parse the next character from the VARIABLE state
		/// </summary>
		/// <param name="c">Character to parse</param>
		/// <returns>false if the character can't work after VARIABLE</returns>
		bool ParseVar(char c);

		/// <summary>
		/// Parse the next character from the CLOSED_PARENTHESIS state
		/// </summary>
		/// <param name="c">Character to parse</param>
		/// <returns>false if the character can't work after CLOSED_PARENTHESIS</returns>
		bool ParseClosedPar(char c);

		/// <summary>
		/// Finish building an int and add to the tree
		/// </summary>
		void CompleteInt();

		/// <summary>
		/// Finished building a float and add to the tree
		/// </summary>
		void CompleteFloat();

		/// <summary>
		/// Finishes parsing a string of characters by adding either a unary operator or a group of variables.
		/// </summary>
		/// <returns>True if the string was a variable.</returns>
		bool CompleteString();

		ParserState state_;
		string input_;
		unique_ptr<ExpTree> tree_;
		string cache_;
		int parenthesis_depth;
		int position_;
		map<string, Operator> operator_map =
		{
			{ "sin", Operator::SINE },
			{ "cos", Operator::COSINE },
			{ "tan", Operator::TANGENT },
			{ "csc", Operator::COSECANT },
			{ "sec", Operator::SECANT },
			{ "cot", Operator::COTANGENT, }
		};
};

/// <summary>
/// Get an ExpTree from an equation string
/// </summary>
/// <param name="c">Character to parse</param>
/// <returns>false if the character can't work in BEGIN</returns>
int Parse(const string& equation, unique_ptr<ExpTree>& tree);
