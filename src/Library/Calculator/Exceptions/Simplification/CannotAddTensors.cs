// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.Operations;

namespace Calculator.Exceptions.Simplification
{
    public class CannotAddTensors : SimplificationException
    {
        public CannotAddTensors(Simplifier simplifier, ExpNode context, string message = "")
            : base(simplifier, context, message) { }
    }
}
