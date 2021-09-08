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
    }
}
