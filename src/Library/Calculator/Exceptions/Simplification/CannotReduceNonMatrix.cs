// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.Operations;
using System;

namespace Calculator.Exceptions.Simplification
{
    /// <summary>
    /// A <see cref="CannotReduceNonMatrix"/> for when reducing a non-matrix <see cref="ExpNode"/>.
    /// </summary>
    public class CannotReduceNonMatrix : SimplificationException
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CannotReduceNonMatrix"/> class.
        /// </summary>
        /// <param name="simplifier">The simplified that threw.</param>
        /// <param name="context">The <see cref="ExpNode"/> that it threw simplifying.</param>
        /// <param name="message">The <see cref="Exception"/> message.</param>
        public CannotReduceNonMatrix(Simplifier simplifier, ExpNode context, string message = "")
            : base(simplifier, context, message) { }
    }
}
