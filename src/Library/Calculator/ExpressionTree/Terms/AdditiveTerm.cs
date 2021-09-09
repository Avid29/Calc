// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Printers.Default;
using System;

namespace Calculator.ExpressionTree.Terms
{
    public class AdditiveTerm : IEquatable<AdditiveTerm>, IComparable<AdditiveTerm>
    {
        private double _coefficient;
        private ExpNode _base;
        private string _baseString;

        public AdditiveTerm(ExpNode node)
        {
            DefaultPrinter printer = new DefaultPrinter();
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

        public ExpNode AsExpNode()
        {
            if (_coefficient == 0) return Helpers.MakeNumericalNode(0);
            if (_coefficient == 1) return _base;
            return Helpers.Multiply(_coefficient, _base);
        }

        public void AddToCoefficient(AdditiveTerm other)
        {
            _coefficient += other._coefficient;
        }

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

        public bool Equals(AdditiveTerm other)
        {
            return _baseString == other._baseString;
        }
    }
}
