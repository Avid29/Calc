using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpTree.Nodes.Operators.UOpers.SineNode
{
    public class SineOperNode : UOperNode
    {
        public override Priority Priority => Priority.FUNCTION;

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
