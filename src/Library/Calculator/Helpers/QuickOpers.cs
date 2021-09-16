// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpressionTree.Nodes.Values;

namespace Calculator.Helpers
{
    /// <summary>
    /// A class containing methods that quickly applys <see cref="OperNode"/>s to <see cref="ExpNode"/>s.
    /// </summary>
    public static class QuickOpers
    {
        /// <summary>
        /// Creates a new <see cref="NumericalValueNode"/> for a value.
        /// </summary>
        /// <param name="value">The value of the node.</param>
        /// <returns>A new <see cref="NumericalValueNode"/> with <paramref name="value"/>.</returns>
        public static NumericalValueNode MakeNumericalNode(double value)
        {
            // Check if value is an int
            int intValue = (int)value;
            if (value == intValue)
            {
                // value is an int
                return new IntValueNode(intValue);
            }

            return new FloatValueNode(value);
        }

        /// <summary>
        /// Creates a new <see cref="AdditionOperNode"/> summing <paramref name="nodes"/>.
        /// </summary>
        /// <param name="nodes">The expressions to add.</param>
        /// <returns>A new <see cref="AdditionOperNode"/> summing <paramref name="nodes"/>.</returns>
        public static AdditionOperNode Sum(params ExpNode[] nodes)
        {
            // Create an addition node with all nodes as children
            AdditionOperNode aNode = new();
            foreach (var node in nodes) aNode.AddChild(node);
            return aNode;
        }

        /// <summary>
        /// Creates a new <see cref="AdditionOperNode"/> adding <paramref name="value"/> and <paramref name="node"/>.
        /// </summary>
        /// <param name="value">The value to add as a <see cref="NumericalValueNode"/>.</param>
        /// <param name="node">The expression to add.</param>
        /// <returns>A new <see cref="AdditionOperNode"/> adding <paramref name="value"/> and <paramref name="node"/>.</returns>
        public static AdditionOperNode Add(double value, ExpNode node)
        {
            return Sum(MakeNumericalNode(value), node);
        }

        /// <summary>
        /// Creates a new <see cref="MultiplicationOperNode"/> multiplying <paramref name="nodes"/>.
        /// </summary>
        /// <param name="nodes">The expressions to multiply.</param>
        /// <returns>A new <see cref="MultiplicationOperNode"/> multiplying <paramref name="nodes"/>.</returns>
        public static MultiplicationOperNode Multiply(params ExpNode[] nodes)
        {
            // Create a multiplication node with all nodes as children
            MultiplicationOperNode mNode = new();
            foreach (var node in nodes) mNode.AddChild(node);
            return mNode;
        }

        /// <summary>
        /// Creates a new <see cref="MultiplicationOperNode"/> multiplying <paramref name="value"/> and <paramref name="node"/>.
        /// </summary>
        /// <param name="value">The value to multiply as a <see cref="NumericalValueNode"/>.</param>
        /// <param name="node">The expression to multiply.</param>
        /// <returns>A new <see cref="MultiplicationOperNode"/> multiplying <paramref name="value"/> and <paramref name="node"/>.</returns>
        public static MultiplicationOperNode Multiply(double value, ExpNode node)
        {
            return Multiply(MakeNumericalNode(value), node);
        }

        /// <summary>
        /// Creates a new negative <see cref="SignOperNode"/> around <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="ExpNode"/> to negate.</param>
        /// <returns>A new negative <see cref="SignOperNode"/> around <paramref name="node"/>.</returns>
        public static SignOperNode Negative(ExpNode node)
        {
            return new SignOperNode(Sign.NEGATIVE) { Child = node };
        }

        /// <summary>
        /// Creates a new <see cref="PowOperNode"/> as <paramref name="base"/>^<paramref name="exponent"/>.
        /// </summary>
        /// <param name="base">The base of the <see cref="PowOperNode"/>.</param>
        /// <param name="exponent">The exponent of the <see cref="PowOperNode"/>.</param>
        /// <returns>A new <see cref="PowOperNode"/> as <paramref name="base"/>^<paramref name="exponent"/>.</returns>
        public static PowOperNode Pow(ExpNode @base, ExpNode exponent)
        {
            PowOperNode powNode = new();
            powNode.LeftChild = @base;
            powNode.RightChild = exponent;
            return powNode;
        }

        /// <summary>
        /// Creates a new <see cref="PowOperNode"/> as <paramref name="base"/>^<paramref name="exponent"/>.
        /// </summary>
        /// <param name="base">The base of the <see cref="PowOperNode"/>.</param>
        /// <param name="exponent">The exponent of the <see cref="PowOperNode"/>.</param>
        /// <returns>A new <see cref="PowOperNode"/> as <paramref name="base"/>^<paramref name="exponent"/>.</returns>
        public static PowOperNode Pow(ExpNode @base, double exponent)
        {
            return Pow(@base, MakeNumericalNode(exponent));
        }

        /// <summary>
        /// Creates a new <see cref="RecipricalOperNode"/> around <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="ExpNode"/> to take the reciprical of.</param>
        /// <returns>A new <see cref="RecipricalOperNode"/> around <paramref name="node"/>.</returns>
        public static RecipricalOperNode Reciprical(ExpNode node)
        {
            return new RecipricalOperNode() { Child = node };
        }
    }
}
