// Adam Dernis © 2021

namespace Calculator.Parser.Default
{
    /// <summary>
    /// The parser's state.
    /// </summary>
    public enum ParserState
    {
        /// <summary>
        /// The beginning of an expression.
        /// </summary>
        BEGIN,

        /// <summary>
        /// The beginning of an expression in side parenthesis.
        /// </summary>
        OPEN_PARENTHESIS,

        /// <summary>
        /// After an NOperNode was added.
        /// </summary>
        NOPER,

        /// <summary>
        /// After a UOperNode was added.
        /// </summary>
        UOPER,

        /// <summary>
        /// Forming an integer.
        /// </summary>
        INT,

        /// <summary>
        /// Last character was a decimal moving changing from int to float.
        /// </summary>
        DECIMAL,

        /// <summary>
        /// Forming a floating point value.
        /// </summary>
        FLOAT,

        /// <summary>
        /// Last added an effective value to the tree.
        /// </summary>
        VALUE,

        /// <summary>
        /// Last added a variable to the tree.
        /// </summary>
        VARIABLE,

        /// <summary>
        /// Parsing a function's name.
        /// </summary>
        PARTIAL_FUNCTION,

        /// <summary>
        /// Parsing is being handled by a function parser
        /// </summary>
        FUNCTION,


        // Finished states

        /// <summary>
        /// Parsing successfully completed.
        /// </summary>
        DONE,

        /// <summary>
        /// There was an error in parsing the string.
        /// </summary>
        ERROR,
    }
}
