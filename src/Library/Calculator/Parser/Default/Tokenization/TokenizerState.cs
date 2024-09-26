// Adam Dernis 2024

namespace Calculator.Parser.Default.Tokenization;

/// <summary>
/// An enum to track the evaulation state of the tokenizer.
/// </summary>
public enum TokenizerState
{
    /// <summary>
    /// The beginning of a token. All tokens begin processing from <see langword="this"/> state.
    /// </summary>
    Begin,

    /// <summary>
    /// Building an integer.
    /// </summary>
    Integer,

    /// <summary>
    /// Building a float.
    /// </summary>
    Float,

    /// <summary>
    /// Building a function.
    /// </summary>
    Function,

    /// <summary>
    /// The tokenizer has completed.
    /// </summary>
    Done,

    /// <summary>
    /// There was an error tokenizing.
    /// </summary>
    Error,
}
