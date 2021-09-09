// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Operators;

namespace Calculator.Exceptions.ExpressionTree
{
    /// <summary>
    /// An <see cref="ExpNodeException"/> for when a child is added to a <see cref="UOperNode"/> that already has its child.
    /// </summary>
    public class UOperNodeAlreadyHasChildException : ExpNodeException
    {
        private const string MESSAGE = "Cannot add child to UOperNode because it already contains a child";

        /// <summary>
        /// Initializes a new instance of the <see cref="UOperNodeAlreadyHasChildException"/> class.
        /// </summary>
        /// <param name="node">The <see cref="UOperNode"/> throwing.</param>
        public UOperNodeAlreadyHasChildException(UOperNode node)
            : base(node, MESSAGE) { }
    }
}
