#include "include/ParserErrors.h"

string ParseErrorToString(ParserState error, string& input, int positon) {
	ostringstream stringStream;
	switch (error)
	{
		case ParserState::CANNOT_PROCEED:
			stringStream << "'" << input[positon]
				<< "' cannot proceed '" << input[positon - 1] << "'.";
			break;

		case ParserState::UNPAIRED_PARENTHESIS:
			stringStream << "Parenthesis unbalanced.";
			break;

		case ParserState::ALREADY_FLOAT:
			stringStream << "Decimal not allowed when number is already a float.";
			break;

		case ParserState::UNKNOWN_ERROR:
			stringStream << "Unknown error.";
			break;
	}
	stringStream << endl;
	return stringStream.str();
}