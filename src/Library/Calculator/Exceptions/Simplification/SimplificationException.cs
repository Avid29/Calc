// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.Operations;
using System;

namespace Calculator.Exceptions.Simplification
{
    public abstract class SimplificationException : Exception
    {
        protected SimplificationException(Simplifier simplifier, ExpNode context, string message = "")
            : base(message)
        {
            Simplifier = simplifier;
            Context = context;
        }

        public Simplifier Simplifier { get; }

        public ExpNode Context { get; }
    }
}
