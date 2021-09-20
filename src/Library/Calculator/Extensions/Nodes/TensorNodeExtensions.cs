// Adam Dernis © 2021

namespace Calculator.ExpressionTree.Nodes.Collections
{
    /// <summary>
    /// A class for node extension methods.
    /// </summary>
    public static class TensorNodeExtensions
    {
        /// <summary>
        /// Checks if two <see cref="TensorNode"/>s are the same size.
        /// </summary>
        /// <param name="node">The first <see cref="TensorNode"/>.</param>
        /// <param name="other">The second <see cref="TensorNode"/>.</param>
        /// <returns>True if the two tensors are equal size.</returns>
        public static bool AreEqualSize(this TensorNode node, TensorNode other)
        {
            return node.SizeIdentity == other.SizeIdentity;
        }

        /// <summary>
        /// Checks if two <see cref="TensorNode"/>s are vectors and equal size.
        /// </summary>
        /// <param name="node">The first <see cref="TensorNode"/>.</param>
        /// <param name="other">The second <see cref="TensorNode"/>.</param>
        /// <returns>True if two <see cref="TensorNode"/>s are equal size and vectors.</returns>
        public static bool AreEqualSizeVectors(this TensorNode node, TensorNode other)
        {
            return node.DimensionCount == 1 && node.AreEqualSize(other);
        }

        /// <summary>
        /// Checks if two <see cref="TensorNode"/>s are vectors and equal size.
        /// </summary>
        /// <param name="node">The first <see cref="ExpNode"/>.</param>
        /// <param name="other">The second <see cref="ExpNode"/>.</param>
        /// <param name="vector1">The first <see cref="ExpNode"/> as a <see cref="TensorNode"/>.</param>
        /// <param name="vector2">The second <see cref="ExpNode"/> as a <see cref="TensorNode"/>.</param>
        /// <returns>True if two <see cref="TensorNode"/>s are equal size and vectors.</returns>
        public static bool AreEqualSizeVectors(this ExpNode node, ExpNode other, out TensorNode vector1, out TensorNode vector2)
        {
            if (node is TensorNode tensor1 && other is TensorNode tensor2)
            {
                vector1 = tensor1;
                vector2 = tensor2;
                return AreEqualSizeVectors(tensor1, tensor2);
            }

            vector1 = vector2 = null;
            return false;
        }

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
