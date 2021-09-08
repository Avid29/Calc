﻿using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.Functions;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Printers.Abstract;

namespace Calculator.Printers.Default
{
    public class DefaultPrinter : Printer
    {
        public override string Print(AdditionOperNode node)
        {
            string cache = "";
            for (int i = 0; i < node.ChildCount; i++)
            {
                var child = node.GetChild(i);
                bool isSignChild = child is SignOperNode;
                if (!(i == 0 || isSignChild))
                {
                    // Don't add if isSignChild
                    // or if first iteration
                    cache += "+";
                }

                cache += child.Print(this);
            }
            return cache;
        }

        public override string Print(ExpNode node)
        {
            return "";
        }

        public override string Print(DiffOperNode node)
        {
            return $"\\diff[{node.Variable.Print(this)}]{{{node.Child.Print(this)}}}";
        }

        public override string Print(FloatValueNode node)
        {
            return $"{node.Value}";
        }

        public override string Print(IntegralOperNode node)
        {
            if (node.IsDeterminate)
                return $"\\int[{node.Variable.Print(this)}]{{{node.Child.Print(this)}}}";
            else
                return $"\\int[{node.Variable.Print(this)}, {node.LowerBound.Print(this)}, {node.UpperBound.Print(this)}]{{{node.Child.Print(this)}}}";
        }

        public override string Print(IntValueNode node)
        {
            return $"{node.Value}";
        }

        public override string Print(MultiplicationOperNode node)
        {
            string cache = "";
            for (int i = 0; i < node.ChildCount; i++)
            {
                cache += node.GetChild(i).Print(this);
            }
            return cache;
        }

        public override string Print(PowOperNode node)
        {
            return $"{node.LeftChild.Print(this)}^{node.RightChild.Print(this)}";
        }

        public override string Print(SignOperNode node)
        {
            switch (node.Sign)
            {
                case Sign.POSITIVE:
                    return $"+{node.Child.Print(this)}";
                case Sign.NEGATIVE:
                    return $"-{node.Child.Print(this)}";
                default:
                    return node.Child.Print(this);
            }
        }

        public override string Print(VarValueNode node)
        {
            return $"{node.Character}";
        }
    }
}
