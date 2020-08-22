#pragma once

#include <string>

class Error {
public:
	enum class ErrorType {
		NONE,
		UNKNOWN,
		GENERIC,
		CANNOT_BEGIN,
		CANNOT_PROCEED,
		UNPAIRED_PARENTHESIS,
		INVALID_FUNCTION,
		ALREADY_FLOAT,
		DERIVATIVE_MUST_BE_VARIABLE,
	};

	Error();

	Error(ErrorType error, std::string input, int position);

	/// <summary>
	/// Gets the type of error from parsing.
	/// </summary>
	/// <returns>The error type.</returns>
	ErrorType GetErrorType() const;

	/// <summary>
	/// Gets the string entered into the parser where the error occured.
	/// </summary>
	/// <returns>The string parsed with the error.</returns>
	std::string GetInput() const;

	/// <summary>
	/// Gets the position of the parsing progress with the error.
	/// </summary>
	/// <returns>The position of parsing where the error occured.</returns>
	int GetPosition() const;

private:
	ErrorType error_;
	std::string input_;
	int position_;
};