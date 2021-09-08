using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.UOpers
{
    public class ParenthesisOperNode : UOperNode
    {
        public ParenthesisOperNode()
        {
            IsOpen = true;
        }

        public override Priority Priority => IsOpen ? Priority.OVERRIDE : Priority.VALUE;

        public bool IsOpen { get; set; }

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
