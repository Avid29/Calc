// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Operators;

namespace Calculator.Exceptions.ExpressionTree
{
    /// <summary>
    /// An <see cref="ExpNodeException"/> for when a child is added to a <see cref="BOperNode"/> that already has all its children.
    /// </summary>
    public class BOperNodeAlreadyHasChildrenException : ExpNodeException
    {
        private const string MESSAGE = "Cannot add child to BOperNode because it already contains a two (2) children";

        /// <summary>
        /// Initializes a new instance of the <see cref="BOperNodeAlreadyHasChildrenException"/> class.
        /// </summary>
        /// <param name="node">The <see cref="BOperNode"/> throwing.</param>
        public BOperNodeAlreadyHasChildrenException(BOperNode node)
            : base(node, MESSAGE) { }
    }
}
