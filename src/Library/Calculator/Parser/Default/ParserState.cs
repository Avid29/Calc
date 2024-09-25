// Adam Dernis 2024

namespace Calculator.Parser.Default;

/// <summary>
/// The parser's state.
/// </summary>
public enum ParserState
{
    /// <summary>
    /// The beginning of an expression.
    /// </summary>
    Begin,

    /// <summary>
    /// The beginning of an expression in side parenthesis.
    /// </summary>
    OpenParenthesis,

    /// <summary>
    /// After an NOperNode was added.
    /// </summary>
    NOper,

    /// <summary>
    /// After a UOperNode was added.
    /// </summary>
    UOper,

    /// <summary>
    /// Forming an integer.
    /// </summary>
    Integer,

    /// <summary>
    /// Last character was a decimal moving changing from int to float.
    /// </summary>
    Decimal,

    /// <summary>
    /// Forming a floating point value.
    /// </summary>
    Float,

    /// <summary>
    /// Last added an effective value to the tree.
    /// </summary>
    Value,

    /// <summary>
    /// Last added a variable to the tree.
    /// </summary>
    Variable,

    /// <summary>
    /// Parsing a function's name.
    /// </summary>
    PartialFunction,

    /// <summary>
    /// Parsing is being handled by a function parser
    /// </summary>
    Function,


    // Finished states

    /// <summary>
    /// Parsing successfully completed.
    /// </summary>
    Done,

    /// <summary>
    /// There was an error in parsing the string.
    /// </summary>
    Error,
}
