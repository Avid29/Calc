#include "include/ParserErrors.h"

string ParseErrorToString(ParserState error, string& input, int positon) {
	ostringstream stringStream;
	switch (error)
	{
		case ParserState::CANNOT_PROCEED:
			stringStream << "'" << input[positon]
				<< "' cannot proceed '" << input[positon - 1] << "'";
			break;

		case ParserState::UNPAIRED_PARENTHESIS:
			stringStream << "Parenthesis unbalanced.";
			break;

		case ParserState::UNKNOWN_ERROR:
			stringStream << "Unknown error";
			break;
	}
	stringStream << endl;
	return stringStream.str();
}