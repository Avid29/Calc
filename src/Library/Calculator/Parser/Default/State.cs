namespace Calculator.Parser.Default
{
    public enum State
    {
        BEGIN, // The beginning of an expression
        OPEN_PARENTHESIS,
        NOPER, // Nary (or binary) operator
        UOPER, // Unary operator
        INT,
        DECIMAL,
        FLOAT,
        VALUE,
        VARIABLE,
        PARTIAL_FUNCTION, // Parsing the function name
        FUNCTION, // Parsing is being handled by a function parser

        // Finished states
        DONE,
        ERROR,
    }
}
