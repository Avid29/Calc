using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.Functions
{
    public class DiffOperNode : UOperNode
    {
        public override Priority Priority => Priority.OVERRIDE;

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
