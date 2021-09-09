// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.NOpers
{
    public class AdditionOperNode : NOperNode
    {
        public AdditionOperNode() { }

        public AdditionOperNode(AdditionOperNode node)
            : base(node) { }

        public override Priority Priority => Priority.ADDITION;

        public override ExpNode Clone()
        {
            return new AdditionOperNode(this);
        }

        public override ExpNode Execute(Operation operation)
        {
            return operation.Execute(this);
        }

        public override string Print(Printer printer)
        {
            return printer.Print(this);
        }
    }
}
