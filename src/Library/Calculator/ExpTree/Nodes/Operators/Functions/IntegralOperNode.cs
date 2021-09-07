using Calculator.ExpTree.Nodes.Values;
using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpTree.Nodes.Operators.Functions
{
    public class IntegralOperNode : UOperNode
    {
        public override Priority Priority => Priority.FUNCTION;

        public bool IsDeterminate { get; set; }

        public VarValueNode Variable { get; }

        public ExpNode UpperBound { get; set; }

        public ExpNode LowerBound { get; set; }

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
