// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using System;

namespace Calculator.Exceptions.ExpressionTree
{
    public class ExpNodeException : Exception
    {
        public ExpNodeException(ExpNode expNode, string message = null)
            : base(message)
        {
            Node = expNode;
        }

        public ExpNode Node { get; }
    }
}
