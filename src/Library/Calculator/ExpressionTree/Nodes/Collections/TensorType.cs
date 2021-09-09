// Adam Dernis © 2021

namespace Calculator.ExpressionTree.Nodes.Collections
{
    /// <summary>
    /// The type of <see cref="TensorNode"/>.
    /// </summary>
    public enum TensorType : int
    {
        /// <summary>
        /// A vector.
        /// </summary>
        Vector = 1,

        /// <summary>
        /// A matrix.
        /// </summary>
        Matrix = 2,

        /// <summary>
        /// A tensor.
        /// </summary>
        Tensor,
    }
}
