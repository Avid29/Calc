// Adam Dernis © 2021

namespace Calculator.Parser.Default.Status
{
    /// <summary>
    /// A partial parser status containing simply error info.
    /// </summary>
    public class ParseError
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="ParseError"/> class.
        /// </summary>
        public ParseError()
            : this(ErrorType.NONE)
        { }

        /// <summary>
        /// Initializes a new instance of the <see cref="ParseError"/> class as a partial clone of <see cref="ParserStatus"/>.
        /// </summary>
        /// <param name="status">The full <see cref="ParserStatus"/> to create a <see cref="ParseError"/> from.</param>
        public ParseError(ParserStatus status)
        {
            ErrorType = status.ErrorType;
            ExpectedCharacter = status.ExpectedCharacter;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="ParseError"/> class.
        /// </summary>
        /// <param name="error">The error type.</param>
        /// <param name="expected">The expected character.</param>
        public ParseError(ErrorType error, char expected = '\0')
        {
            ErrorType = error;
            ExpectedCharacter = expected;
        }

        /// <summary>
        /// Gets or sets the type of error that occured.
        /// </summary>
        public ErrorType ErrorType { get; protected set; }

        /// <summary>
        /// Gets or sets the character that was expected.
        /// </summary>
        public char ExpectedCharacter { get; protected set; }

        /// <summary>
        /// Gets a value indicating whether or not the error indicates a failure.
        /// </summary>
        public bool Failed => ErrorType != ErrorType.NONE;
    }
}
