// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.Operations;
using System;

namespace Calculator.Exceptions.Simplification
{
    /// <summary>
    /// An <see cref="Exception"/> thrown or given while simplifying.
    /// </summary>
    public abstract class SimplificationException : Exception
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="SimplificationException"/> class.
        /// </summary>
        /// <param name="simplifier">The simplified that threw.</param>
        /// <param name="context">The <see cref="ExpNode"/> that it threw simplifying.</param>
        /// <param name="message">The <see cref="Exception"/> message.</param>
        protected SimplificationException(Simplifier simplifier, ExpNode context, string message = "")
            : base(message)
        {
            Simplifier = simplifier;
            Context = context;
        }

        /// <summary>
        /// Gets the <see cref="Operations.Simplifier"/>.
        /// </summary>
        public Simplifier Simplifier { get; }

        /// <summary>
        /// Gets the <see cref="ExpNode"/> that could not be simplified.
        /// </summary>
        public ExpNode Context { get; }
    }
}
