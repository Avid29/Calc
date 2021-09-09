// Adam Dernis © 2021

namespace Calculator.ExpressionTree.Nodes
{
    /// <summary>
    /// The priority of the operation in order of operations.
    /// </summary>
    public enum Priority
    {
        /// <summary>
        /// Overrides all priorties and things in it occur first.
        /// </summary>
        OVERRIDE = -1,

        /// <summary>
        /// A value (not an operation).
        /// </summary>
        VALUE,

        /// <summary>
        /// Signs are handled first.
        /// </summary>
        SIGN,

        /// <summary>
        /// Power (exponent).
        /// </summary>
        POWER,

        /// <summary>
        /// Multiplication.
        /// </summary>
        MULTIPLICATION,

        /// <summary>
        /// Addition
        /// </summary>
        ADDITION,
    }
}
