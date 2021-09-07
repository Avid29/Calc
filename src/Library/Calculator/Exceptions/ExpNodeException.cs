using Calculator.ExpTree.Nodes;
using System;

namespace Calculator.Exceptions
{
    public class ExpNodeException : Exception
    {
        public ExpNodeException(ExpNode expNode, string message = null) : base(message)
        {
            Node = expNode;
        }

        public ExpNode Node { get; }
    }
}
