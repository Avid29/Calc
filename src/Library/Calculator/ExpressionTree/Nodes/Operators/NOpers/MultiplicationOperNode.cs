using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.NOpers
{
    public class MultiplicationOperNode : NOperNode
    {
        public MultiplicationOperNode() { }

        public MultiplicationOperNode(NOperNode node) : base(node) { }

        public override Priority Priority => Priority.MULTIPLICATION;

        public override ExpNode Clone()
        {
            return new MultiplicationOperNode(this);
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
