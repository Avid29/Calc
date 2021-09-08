using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.UOpers
{
    public class ParenthesisOperNode : UOperNode
    {
        public ParenthesisOperNode()
        {
            IsClosed = false;
        }

        public ParenthesisOperNode(ParenthesisOperNode node) : base(node)
        {
            IsClosed = node.IsClosed;
        }

        public override Priority Priority => IsClosed ? Priority.VALUE : Priority.OVERRIDE;

        public bool IsClosed { get; set; }

        public override ExpNode Clone()
        {
            return new ParenthesisOperNode(this);
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
