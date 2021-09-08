using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Values
{
    public class FloatValueNode : ValueNode
    {
        public FloatValueNode(double value)
        {
            Value = value;
        }

        public double Value { get; }

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
