// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;

namespace Calculator.Helpers.Simplification
{
    /// <summary>
    /// A class containing methods for helping with power simplification.
    /// </summary>
    public static class PowerHelpers
    {
        /// <summary>
        /// Applies the power distributive property.
        /// </summary>
        /// <param name="node">The <see cref="PowOperNode"/> to simplify.</param>
        /// <returns>The resuling <see cref="ExpNode"/>.</returns>
        public static ExpNode Distribute(PowOperNode node)
        {
            if (node.LeftChild is ParenthesisOperNode parNode)
            {
                // Child is parenthesis
                // Check for multiplication
                if (parNode.Child is MultiplicationOperNode mNode)
                {
                    // Grand child is multiplication
                    // Distribute
                    for (int i = 0; i < mNode.ChildCount; i++)
                    {
                        PowOperNode pow = QuickOpers.Pow(mNode.GetChild(i), node.RightChild.Clone());
                        mNode.ReplaceChild(pow, i);
                    }
                    return mNode;
                }
            }
            return node;
        }
    }
}
