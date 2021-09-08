using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.BOpers
{
    public class PowOperNode : BOperNode
    {
        public override Priority Priority => Priority.POWER;

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
