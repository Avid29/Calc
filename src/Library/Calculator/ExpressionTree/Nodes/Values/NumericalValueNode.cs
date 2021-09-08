namespace Calculator.ExpressionTree.Nodes.Values
{
    public abstract class NumericalValueNode : ValueNode
    {
        public abstract double DoubleValue { get; }
    }
}
