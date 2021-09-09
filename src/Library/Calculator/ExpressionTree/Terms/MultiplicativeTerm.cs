// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Operations;
using Calculator.Operations.Abstract;
using Calculator.Printers.Default;
using System;

namespace Calculator.ExpressionTree.Terms
{
    /// <summary>
    /// Represents a term of an multiplication operation.
    /// </summary>
    public class MultiplicativeTerm : IEquatable<MultiplicativeTerm>, IComparable<MultiplicativeTerm>
    {
        private readonly ExpNode _base;
        private readonly string _baseString;
        private ExpNode _exponent;

        /// <summary>
        /// Initializes a new instance of the <see cref="MultiplicativeTerm"/> class.
        /// </summary>
        /// <param name="node">The node to create as a term.</param>
        public MultiplicativeTerm(ExpNode node)
        {
            DefaultPrinter printer = new();
            if (node is PowOperNode powNode)
            {
                _base = powNode.LeftChild;
                _exponent = powNode.RightChild;
            } else
            {
                _base = node;
                _exponent = Helpers.MakeNumericalNode(1);
            }
            _baseString = _base.Print(printer);
        }

        /// <summary>
        /// Converts the <see cref="NumericalValueNode"/> back to an <see cref="ExpNode"/>.
        /// </summary>
        /// <returns>The <see cref="NumericalValueNode"/> as an <see cref="ExpNode"/>.</returns>
        public ExpNode AsExpNode()
        {
            if (_exponent is NumericalValueNode nvNode)
            {
                if (nvNode.DoubleValue == 0)
                {
                    return Helpers.MakeNumericalNode(1);
                } else if (nvNode.DoubleValue == 1)
                {
                    return _base;
                }
            }

            return Helpers.Pow(_base, _exponent);
        }

        /// <summary>
        /// Adds the exponent of another <see cref="MultiplicativeTerm"/>.
        /// </summary>
        /// <param name="other">The other <see cref="MultiplicativeTerm"/>.</param>
        /// <param name="simplifier">The <see cref="Simplifier"/> to simplify with after adding.</param>
        public void AddToExponent(MultiplicativeTerm other, Simplifier simplifier)
        {
            _exponent = Helpers.Sum(_exponent, other._exponent).Execute(simplifier);
        }

        /// <inheritdoc/>
        public int CompareTo(MultiplicativeTerm other)
        {
            if (_base is NumericalValueNode)
            {
                // Numbers first
                return -1;
            }
            else if (other._base is NumericalValueNode)
            {
                // Numbers first
                return 1;
            }
            else if (!string.IsNullOrEmpty(_baseString) && _baseString[0] == '(')
            {
                // Parenthesis last
                return 1;
            }
            else if (!string.IsNullOrEmpty(other._baseString) && other._baseString[0] == '(')
            {
                // Parenthesis last
                return -1;
            }

            // Arbitrary comparsing to confirm order of like terms
            return _baseString.CompareTo(other._baseString);
        }

        /// <inheritdoc/>
        public bool Equals(MultiplicativeTerm other) => _baseString == other._baseString;
    }
}
