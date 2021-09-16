// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Helpers;
using Calculator.Printers.Default;
using System;

namespace Calculator.Operations.Groups.Terms
{
    /// <summary>
    /// Represents a term of an addition operation.
    /// </summary>
    public class AdditiveTerm : IEquatable<AdditiveTerm>, IComparable<AdditiveTerm>
    {
        private readonly ExpNode _base;
        private readonly string _baseString;
        private double _coefficient;

        /// <summary>
        /// Initializes a new instance of the <see cref="AdditiveTerm"/> class.
        /// </summary>
        /// <param name="node">The node to create as a term.</param>
        public AdditiveTerm(ExpNode node)
        {
            DefaultPrinter printer = new();
            if (node is MultiplicationOperNode mNode && mNode.GetChild(0) is NumericalValueNode nvNode)
            {
                // Node is a multiply and it's first child is a numerical value
                // That numerical value is the coefficient
                _coefficient = nvNode.DoubleValue;

                // Remove coefficient from base
                mNode.RemoveChild(0);
                _base = mNode;
            } else
            {
                _coefficient = 1;
                _base = node;
            }

            _baseString = _base.Print(printer);
        }

        /// <summary>
        /// Converts the <see cref="AdditiveTerm"/> back to an <see cref="ExpNode"/>.
        /// </summary>
        /// <returns>The <see cref="AdditiveTerm"/> as an <see cref="ExpNode"/>.</returns>
        public ExpNode AsExpNode()
        {
            if (_coefficient == 0) return QuickOpers.MakeNumericalNode(0);
            if (_coefficient == 1) return _base;
            return QuickOpers.Multiply(_coefficient, _base);
        }

        /// <summary>
        /// Adds the coefficient of another <see cref="AdditiveTerm"/>.
        /// </summary>
        /// <param name="other">The other <see cref="AdditiveTerm"/>.</param>
        public void AddToCoefficient(AdditiveTerm other)
        {
            _coefficient += other._coefficient;
        }

        /// <inheritdoc/>
        public int CompareTo(AdditiveTerm other)
        {
            if (_base is NumericalValueNode)
            {
                return 1;
            } else if (other._base is NumericalValueNode)
            {
                return -1;
            } else
            {
                return _baseString.CompareTo(other._baseString);
            }
        }

        /// <inheritdoc/>
        public bool Equals(AdditiveTerm other) => _baseString == other._baseString;
    }
}
