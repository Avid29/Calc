using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Values;

namespace Calculator
{
    public static class Helpers
    {
        public static ValueNode MakeValueNode(double value)
        {
            int intValue = (int)value;
            if (value == intValue)
            {
                return new IntValueNode(intValue);
            }

            return new FloatValueNode(value);
        }

        public static MultiplicationOperNode Multiply(params ExpNode[] nodes)
        {
            MultiplicationOperNode mNode = new MultiplicationOperNode();
            foreach (var node in nodes)
            {
                mNode.AddChild(node);
            }
            return mNode;
        }

        public static MultiplicationOperNode Multiply(double value, ExpNode node)
        {
            return Multiply(MakeValueNode(value), node);
        }
    }
}
