#pragma once

#include <string>

#include "PartialStatus.h"

class Status : public PartialStatus {
public:
	Status();

	Status(std::string input, int position);

	Status(PartialStatus error, std::string input, int position);

	Status(ErrorTypes::ErrorType error, std::string input, int position, char expectedChar = '\0');

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