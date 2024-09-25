// Adam Dernis 2024

namespace Calculator.Parser.Default.Status;

/// <summary>
/// A parser status or error.
/// </summary>
public class ParserStatus : ParseError
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ParserStatus"/> class.
    /// </summary>
    /// <param name="input">The input to the parser.</param>
    /// <param name="position">The position in input of the error.</param>
    public ParserStatus(string input, int position) : base(ErrorType.None)
    {
        Input = input;
        Position = position;
    }

    /// <summary>
    /// Initializes a new instance of the <see cref="ParserStatus"/> class.
    /// </summary>
    /// <param name="error">The <see cref="ParseError"/> of the full error.</param>
    /// <param name="input">The input to the parser.</param>
    /// <param name="position">The position in input of the error.</param>
    public ParserStatus(ParseError error, string input, int position)
        : this(error.ErrorType, input, position, error.ExpectedCharacter)
    { }

    /// <summary>
    /// Initializes a new instance of the <see cref="ParserStatus"/> class.
    /// </summary>
    /// <param name="errorType">The type of error.</param>
    /// <param name="input">The input to the parser.</param>
    /// <param name="position">The position in input of the error.</param>
    /// <param name="expectedChar">The expected character (if not null).</param>
    public ParserStatus(ErrorType errorType, string input, int position, char expectedChar = '\0') : base(errorType, expectedChar)
    {
        Input = input;
        Position = position;
    }

    /// <summary>
    /// Gets the input that the error occured for.
    /// </summary>
    public string Input { get; }

    /// <summary>
    /// Gets the position of the error.
    /// </summary>
    public int Position { get; }
}
