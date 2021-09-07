using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpTree.Nodes.Operators.UOpers
{
    public class RecipricalOperNode : UOperNode
    {
        public override Priority Priority => Priority.SIGN;

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
