#pragma once

#include <stack>
#include <string>
#include <vector>
#include <map>

#include "ExpNode.h"
#include "ExpTree.h"
#include "IFuncParser.h"
#include "NOperNode.h"
#include "SinusoidalFuncParser.h"
#include "UOperNode.h"
#include "VarValueNode.h"

using namespace std;

class LaTeXParser
{
public:
	enum class State {
		BEGIN,
		// Nary (or binary) Operator
		NOPER,
		// Unary Operator
		UOPER,
		INT,
		FLOAT, // Or decimal
		VALUE,
		VARIABLE,
		PARTIAL_FUNCTION,
		FUNCTION,
		DONE,

		// Errors
		UNKNOWN_ERROR,
		GENERIC_ERROR,
		CANNOT_BEGIN,
		CANNOT_PROCEED,
		UNPAIRED_PARENTHESIS,
		INVALID_FUNCTION,
		ALREADY_FLOAT,
	};

	/// <summary>
	/// Initializes a new instance of the LaTeXParser class.
	/// </summary>
	LaTeXParser();

	/// <summary>
	/// Parses a string into a tree
	/// </summary>
	/// <param name="equation">string to parse</param>
	/// <returns>-1 on success, or the invalid character's position</returns>
	int ParseString(const string& equation);

	/// <summary>
	/// Parses the next character into the tree
	/// </summary>
	/// <param name="c">Character to parse</param>
	/// <returns>false if the character can't work in that position</returns>
	bool ParseNextChar(char c);

	/// <summary>
	/// Gets the ExpTree from parser
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

	// TODO: Error printing

	/// <summary>
	/// Gets if parsing is finished
	/// </summary>
	bool IsDone() const;

private:

	/// <summary>
	/// Parses a digit.
	/// </summary>
	/// <param name="c">The exact digit</summary>
	bool ParseDigit(const char c);

	/// <summary>
	/// Parses a letter.
	/// </summary>
	/// <param name="c">The exact letter</summary>
	bool ParseLetter(const char c);

	/// <summary>
	/// Parses an operator
	/// </summary>
	/// <param name="c">The exact operator</summary>
	bool ParseOper(const char c);

	/// <summary>
	/// Parses an nary operator
	/// </summary>
	/// <param name="c">The exact operator</summary>
	bool ParseNOper(const char c);

	/// <summary>
	/// Parses an unary operator
	/// </summary>
	/// <param name="c">The exact operator</summary>
	bool ParseUOper(const char c);
	
	/// <summary>
	/// Parses a bracket.
	/// </summary>
	/// <param name="c">The exact bracket</summary>
	bool ParseBracket(const char c);

	/// <summary>
	/// Parses a '.'.
	/// </summary>
	bool ParseDecimal();

	/// <summary>
	/// Parses a '\'.
	/// </summary>
	bool ParseEscape();

	/// <summary>
	/// Parses any character in the PARTIAL_FUNCTION state.
	/// </summary>
	bool ParsePartialFunc(const char c);

	/// <summary>
	/// Parses any character in the FUNCTION state.
	/// </summary>
	bool ParseFunction(const char c);

	/// <summary>
	/// Finishes building an int or float and adds it to the tree
	/// </summary>
	void CompleteValue();

	State state_;
	string input_;
	unique_ptr<ExpTree> tree_;
	unique_ptr<IFuncParser> active_func_parser;
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
			{ "cot", Operator::COTANGENT, },
	};
};

unique_ptr<IFuncParser> MakeFuncParser(Operator oper);