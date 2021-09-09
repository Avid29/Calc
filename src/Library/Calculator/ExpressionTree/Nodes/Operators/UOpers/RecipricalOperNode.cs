// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.UOpers
{
    public class RecipricalOperNode : UOperNode
    {
        public RecipricalOperNode() { }

        public RecipricalOperNode(RecipricalOperNode node)
            : base(node) { }

        public override Priority Priority => Priority.SIGN;

        public override ExpNode Clone()
        {
            return new RecipricalOperNode(this);
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
