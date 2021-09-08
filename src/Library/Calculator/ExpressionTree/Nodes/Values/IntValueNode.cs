using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Values
{
    public class IntValueNode : NumericalValueNode
    {
        public IntValueNode(IntValueNode node)
        {
            Value = node.Value;
        }

        public IntValueNode(int value)
        {
            Value = value;
        }

        public int Value { get; }

        public override double DoubleValue => Value;

        public override ExpNode Clone()
        {
            return new IntValueNode(this);
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
