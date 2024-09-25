// Adam Dernis 2024

namespace Calculator.ExpressionTree.Nodes;

/// <summary>
/// The priority of the operation in order of operations.
/// </summary>
public enum Priority
{
    /// <summary>
    /// Overrides all priorties and things in it occur first.
    /// </summary>
    Override = -1,

    /// <summary>
    /// A value (not an operation).
    /// </summary>
    Value,

    /// <summary>
    /// Signs are handled first.
    /// </summary>
    Sign,

    /// <summary>
    /// Power (exponent).
    /// </summary>
    Power,

    /// <summary>
    /// Multiplication.
    /// </summary>
    Multiplication,

    /// <summary>
    /// Addition
    /// </summary>
    Addition,
}
