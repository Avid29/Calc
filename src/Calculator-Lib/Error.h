#pragma once

#include <string>

#include "PartialError.h"

class Error : public PartialError {
public:
	Error();

	Error(std::string input, int position);

	Error(PartialError error, std::string input, int position);

	Error(ErrorTypes::ErrorType error, std::string input, int position, char expectedChar = '\0');

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
	std::string input_;
	int position_;
};