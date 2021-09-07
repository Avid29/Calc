using Calculator.ExpTree.Nodes.Values;
using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpTree.Nodes.Operators.Functions
{
    public class DiffOperNode : UOperNode
    {
        public override Priority Priority => Priority.FUNCTION;

        public VarValueNode Variable { get; set; }

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
