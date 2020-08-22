#pragma once

#include <string>

#include "ErrorTypes.h"

enum class ErrorTypes::ErrorType : int;

class PartialError {
public:
	PartialError();

	PartialError(ErrorTypes::ErrorType error, char expectedChar = '\0');

	/// <summary>
	/// Gets the type of error from parsing.
	/// </summary>
	/// <returns>The error type.</returns>
	ErrorTypes::ErrorType GetErrorType() const;

	/// <summary>
	/// Gets the expected character missing to cause the error.
	/// </summary>
	/// <returns>The missing expected character.</returns>
	char GetExpectedChar() const;

protected:
	ErrorTypes::ErrorType error_;
	char expected_char;
};