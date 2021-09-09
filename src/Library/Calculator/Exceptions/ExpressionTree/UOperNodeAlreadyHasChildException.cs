// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Operators;

namespace Calculator.Exceptions.ExpressionTree
{
    public class UOperNodeAlreadyHasChildException : ExpNodeException
    {
        private const string MESSAGE = "Cannot add child to UOperNode because it already contains a child";

        public UOperNodeAlreadyHasChildException(UOperNode node)
            : base(node, MESSAGE) { }
    }
}
