// Adam Dernis © 2021

namespace Calculator.Parser.Default.Status
{
    public class ParseError
    {
        public ParseError()
            : this(ErrorType.NONE)
        { }

        public ParseError(ParserStatus status)
        {
            ErrorType = status.ErrorType;
            ExpectedCharacter = status.ExpectedCharacter;
        }

        public ParseError(ErrorType error, char expected = '\0')
        {
            ErrorType = error;
            ExpectedCharacter = expected;
        }

        public ErrorType ErrorType { get; protected set; }

        public char ExpectedCharacter { get; protected set; }

        public bool Failed => ErrorType != ErrorType.NONE;
    }
}
