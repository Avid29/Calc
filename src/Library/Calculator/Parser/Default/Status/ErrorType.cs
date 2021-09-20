// Adam Dernis © 2021

namespace Calculator.Parser.Default.Status
{
	/// <summary>
	/// The type of error in an <see cref="ParseError"/>.
	/// </summary>
    public enum ErrorType : int
	{
		/// <summary>
		/// There is no error.
		/// </summary>
		NONE,

		/// <summary>
		/// The error is unknown.
		/// </summary>
		UNKNOWN,

		/// <summary>
		/// Expression cannot begin with a character.
		/// </summary>
		CANNOT_BEGIN,

		/// <summary>
		/// Character cannot follow previous character.
		/// </summary>
		CANNOT_PROCEED,

		/// <summary>
		/// A parenthesis has no matching parenthesis.
		/// </summary>
		UNPAIRED_PARENTHESIS,

		/// <summary>
		/// There is no function with provided name.
		/// </summary>
		INVALID_FUNCTION,

		/// <summary>
		/// '.' appeared in after a value that is already a float.
		/// </summary>
		ALREADY_FLOAT,

		/// <summary>
		/// A derivate must contain exclusivly a variable in the first argument.
		/// </summary>
		DERIVATIVE_MUST_BE_VARIABLE,

		/// <summary>
		/// Specific expected character not found.
		/// </summary>
		MUST_BE,

		/// <summary>
		/// When a function declares too few arguments.
		/// </summary>
		INADEQUATE_ARGUMENTS,

		/// <summary>
		/// When a function declares too many arguments.
		/// </summary>
		TOO_MANY_ARGUMENTS,
	}
}
