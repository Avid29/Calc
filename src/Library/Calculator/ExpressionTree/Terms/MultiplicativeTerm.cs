using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Operations.Abstract;
using Calculator.Printers.Default;
using System;

namespace Calculator.ExpressionTree.Terms
{
    public class MultiplicativeTerm : IEquatable<MultiplicativeTerm>, IComparable<MultiplicativeTerm>
    {
        private ExpNode _base;
        private ExpNode _exponent;
        private string _baseString;

        public MultiplicativeTerm(ExpNode node)
        {
            DefaultPrinter printer = new DefaultPrinter();
            if (node is PowOperNode powNode)
            {
                _base = powNode.LeftChild;
                _exponent = powNode.RightChild;
            } else
            {
                _base = node;
                _exponent = Helpers.MakeValueNode(1);
            }
            _baseString = _base.Print(printer);
        }

        public ExpNode AsExpNode()
        {
            if (_exponent is NumericalValueNode nvNode)
            {
                if (nvNode.DoubleValue == 0)
                {
                    return Helpers.MakeValueNode(1);
                } else if (nvNode.DoubleValue == 1)
                {
                    return _base;
                }
            }

            return Helpers.Pow(_base, _exponent);
        }

        public void AddToExponent(MultiplicativeTerm other, Operation operation)
        {
            _exponent = Helpers.Add(_exponent, other._exponent).Execute(operation);
        }

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

        public bool Equals(MultiplicativeTerm other)
        {
            return _baseString == other._baseString;
        }
    }
}
