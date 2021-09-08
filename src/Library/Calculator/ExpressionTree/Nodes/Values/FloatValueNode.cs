using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Values
{
    public class FloatValueNode : NumericalValueNode
    {
        public FloatValueNode(FloatValueNode node)
        {
            Value = node.Value;
        }

        public FloatValueNode(double value)
        {
            Value = value;
        }

        public double Value { get; }

        public override double DoubleValue => Value;

        public override ExpNode Clone()
        {
            throw new System.NotImplementedException();
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
