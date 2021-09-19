// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.ExpressionTree.Nodes.Operators;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Operations;
using System;

namespace Calculator.Exceptions.Simplification
{
    /// <summary>
    /// A <see cref="CannotMultiplyTensors"/> for when adding mismatched <see cref="TensorNode"/>s and <see cref="ValueNode"/>s.
    /// </summary>
    public class CannotMultiplyTensors : SimplificationException
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CannotMultiplyTensors"/> class.
        /// </summary>
        /// <param name="simplifier">The simplified that threw.</param>
        /// <param name="context">The <see cref="OperNode"/> that it threw simplifying.</param>
        /// <param name="message">The <see cref="Exception"/> message.</param>
        public CannotMultiplyTensors(Simplifier simplifier, OperNode context, string message = "")
            : base(simplifier, context, message) { }
    }
}
