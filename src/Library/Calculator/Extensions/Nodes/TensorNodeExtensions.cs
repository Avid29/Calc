// Adam Dernis © 2021

namespace Calculator.ExpressionTree.Nodes.Collections
{
    /// <summary>
    /// A class for node extension methods.
    /// </summary>
    public static class TensorNodeExtensions
    {
        /// <summary>
        /// Checks if two <see cref="TensorNode"/>s can matrix multiply.
        /// </summary>
        /// <param name="node">The first <see cref="TensorNode"/>.</param>
        /// <param name="other">The second <see cref="TensorNode"/>.</param>
        /// <returns>True if the Tensors can multiply as matricies.</returns>
        public static bool CanMatrixMultiply(this TensorNode node, TensorNode other)
        {
            // Ensure both TensorNodes are matricies
            if (node.TensorType != TensorType.Matrix) return false;
            if (other.TensorType != TensorType.Matrix) return false;

            // Ensure node's last dimension is the size of other's first dimension
            return node.GetDimensionSize(2) == other.GetDimensionSize(1);
        }
    }
}
