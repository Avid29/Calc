namespace Calculator.Parser.Default.Status
{
    public class ParserStatus : ParseError
    {
        public ParserStatus(string input, int position)
        {
            Input = input;
            Position = position;
            ErrorType = ErrorType.NONE;
        }

        public ParserStatus(ParseError error, string input, int position) :
            this(error.ErrorType, input, position, error.ExpectedCharacter)
        { }

        public ParserStatus(ErrorType errorType, string input, int position, char expectedChar = '\0')
        {
            Input = input;
            Position = position;
            ErrorType = errorType;
        }

        public string Input { get; }

        public int Position { get; }
    }
}
