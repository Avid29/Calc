namespace Calculator.ExpressionTree.Nodes.Values
{
    public abstract class NumericalValueNode : ValueNode
    {
        public abstract double DoubleValue { get; }

        public override bool IsConstant() => true;

        public override bool IsConstantBy(VarValueNode variable) => true;
    }
}
