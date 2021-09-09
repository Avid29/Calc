// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using System;

namespace Calculator.Exceptions.ExpressionTree
{
    /// <summary>
    /// An <see cref="Exception"/> thrown by an <see cref="ExpNode"/> in parsing.
    /// </summary>
    public abstract class ExpNodeException : Exception
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="ExpNodeException"/> class.
        /// </summary>
        /// <param name="node">The <see cref="ExpNode"/> throwing.</param>
        /// <param name="message">The message of the <see cref="Exception"/>.</param>
        protected ExpNodeException(ExpNode node, string message = null)
            : base(message)
        {
            Node = node;
        }

        /// <summary>
        /// Gets the node that threw.
        /// </summary>
        public ExpNode Node { get; }
    }
}
