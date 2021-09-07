using Calculator.ExpTree.Nodes.Operators;

namespace Calculator.Exceptions.ExpTree
{
    public class UOperNodeAlreadyHasChildException : ExpNodeException
    {
        private const string MESSAGE = "Cannot add child to UOperNode because it already contains a child";

        public UOperNodeAlreadyHasChildException(UOperNode node) : base(node, MESSAGE) { }
    }
}
