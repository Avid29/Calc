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
    /// Last added an effective value to the tree.
    /// </summary>
    Value,

    /// <summary>
    /// Last added a variable to the tree.
    /// </summary>
    Variable,

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
