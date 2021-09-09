// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Operations;
using System;

namespace Calculator.Exceptions.Simplification
{
    /// <summary>
    /// A <see cref="SimplificationException"/> for when adding mismatched <see cref="TensorNode"/>s and <see cref="ValueNode"/>s.
    /// </summary>
    public class CannotAddTensors : SimplificationException
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CannotAddTensors"/> class.
        /// </summary>
        /// <param name="simplifier">The simplified that threw.</param>
        /// <param name="context">The <see cref="ExpNode"/> that it threw simplifying.</param>
        /// <param name="message">The <see cref="Exception"/> message.</param>
        public CannotAddTensors(Simplifier simplifier, ExpNode context, string message = "")
            : base(simplifier, context, message) { }
    }
}
