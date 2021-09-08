using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
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

        public static AdditionOperNode Add(params ExpNode[] nodes)
        {
            AdditionOperNode aNode = new AdditionOperNode();
            foreach (var node in nodes)
            {
                aNode.AddChild(node);
            }
            return aNode;
        }

        public static AdditionOperNode Add(double value, ExpNode node)
        {
            return Add(MakeValueNode(value), node);
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

        public static SignOperNode Negative(ExpNode node)
        {
            return new SignOperNode(Sign.NEGATIVE) { Child = node };
        }

        public static PowOperNode Pow(ExpNode left, ExpNode right)
        {
            PowOperNode powNode = new PowOperNode();
            powNode.LeftChild = left;
            powNode.RightChild = right;
            return powNode;
        }
    }
}
