#pragma once

class ErrorTypes {
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
		MUST_BE,
		EQUALS_CANNOT_BE_MID_EXPRESSION,
	};
};