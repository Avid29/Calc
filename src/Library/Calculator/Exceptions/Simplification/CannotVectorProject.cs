// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.ExpressionTree.Nodes.Operators.Functions;
using Calculator.Operations;
using System;

namespace Calculator.Exceptions.Simplification
{
    /// <summary>
    /// A <see cref="CannotVectorProject"/> for when projecting mismatched <see cref="TensorNode"/>s.
    /// </summary>
    public class CannotVectorProject : SimplificationException
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CannotVectorProject"/> class.
        /// </summary>
        /// <param name="simplifier">The simplified that threw.</param>
        /// <param name="context">The <see cref="VectorProjOperNode"/> that it threw simplifying.</param>
        /// <param name="message">The <see cref="Exception"/> message.</param>
        public CannotVectorProject(Simplifier simplifier, VectorProjOperNode context, string message = "")
            : base(simplifier, context, message) { }
    }
}
