// Adam Dernis 2024

namespace Calculator.Parser.Default.Status;

/// <summary>
/// The type of error in an <see cref="ParseError"/>.
/// </summary>
public enum ErrorType : int
{
    /// <summary>
    /// There is no error.
    /// </summary>
    None,

    /// <summary>
    /// The error is unknown.
    /// </summary>
    Unknown,

    /// <summary>
    /// Expression cannot begin with a character.
    /// </summary>
    CannotBegin,

    /// <summary>
    /// Character cannot follow previous character.
    /// </summary>
    CannotProceed,

    /// <summary>
    /// A parenthesis has no matching parenthesis.
    /// </summary>
    UnpairedParenthesis,

    /// <summary>
    /// There is no function with provided name.
    /// </summary>
    InvalidFunction,

    /// <summary>
    /// '.' appeared in after a value that is already a float.
    /// </summary>
    AlreadyFloat,

    /// <summary>
    /// A derivate must contain exclusivly a variable in the first argument.
    /// </summary>
    DerivativeMustBeVariable,

    /// <summary>
    /// Specific expected character not found.
    /// </summary>
    MustBe,

    /// <summary>
    /// When a function declares too few arguments.
    /// </summary>
    InadequateArguments,

    /// <summary>
    /// When a function declares too many arguments.
    /// </summary>
    TooManyArguments,
}
