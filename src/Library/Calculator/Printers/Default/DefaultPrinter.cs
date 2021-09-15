// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.Functions;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SineNode;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Printers.Abstract;

namespace Calculator.Printers.Default
{
    /// <summary>
    /// The default implementation printer.
    /// </summary>
    public class DefaultPrinter : Printer
    {
        /// <inheritdoc/>
        public override string Print(AdditionOperNode node)
        {
            string cache = string.Empty;

            // Add each child seperated by a '+'
            for (int i = 0; i < node.ChildCount; i++)
            {
                var child = node.GetChild(i);
                bool implicitSign = child is SignOperNode ||
                    ((child is NumericalValueNode nvChild) && nvChild.DoubleValue < 0);
                if (!(i == 0 || implicitSign))
                {
                    // Don't add if is a negative sign operator,
                    // a negative numerical value
                    // or if first iteration
                    cache += "+";
                }

                cache += child.Print(this);
            }
            return cache;
        }

        /// <inheritdoc/>
        public override string Print(ExpNode node)
        {
            return string.Empty;
        }

        /// <inheritdoc/>
        public override string Print(DiffOperNode node)
        {
            return $"\\diff[{node.Variable.Print(this)}]{{{node.Child.Print(this)}}}";
        }

        /// <inheritdoc/>
        public override string Print(FloatValueNode node)
        {
            return $"{node.Value}";
        }

        /// <inheritdoc/>
        public override string Print(IntegralOperNode node)
        {
            if (node.IsDeterminate)
                return $"\\int[{node.Variable.Print(this)}, {node.LowerBound.Print(this)}, {node.UpperBound.Print(this)}]{{{node.Child.Print(this)}}}";
            else
                return $"\\int[{node.Variable.Print(this)}]{{{node.Child.Print(this)}}}";
        }

        /// <inheritdoc/>
        public override string Print(IntValueNode node)
        {
            return $"{node.Value}";
        }

        /// <inheritdoc/>
        public override string Print(MultiplicationOperNode node)
        {
            string cache = string.Empty;

            // No need to seperate with '*'
            // All remain multiplication should be represented with implied
            for (int i = 0; i < node.ChildCount; i++)
            {
                cache += node.GetChild(i).Print(this);
            }
            return cache;
        }

        /// <inheritdoc/>
        public override string Print(ParenthesisOperNode node)
        {
            return $"({node.Child.Print(this)})";
        }

        /// <inheritdoc/>
        public override string Print(PowOperNode node)
        {
            return $"{node.LeftChild.Print(this)}^{node.RightChild.Print(this)}";
        }

        /// <inheritdoc/>
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

        /// <inheritdoc/>
        public override string Print(SineOperNode node)
        {
            switch (node.SineFunction)
            {
                case SineFunction.SINE:
                    return $"\\sin{{{node.Child.Print(this)}}}";
                case SineFunction.COSINE:
                    return $"\\cos{{{node.Child.Print(this)}}}";
                case SineFunction.TANGENT:
                    return $"\\tan{{{node.Child.Print(this)}}}";
                case SineFunction.COSECANT:
                    return $"\\csc{{{node.Child.Print(this)}}}";
                case SineFunction.SECANT:
                    return $"\\sec{{{node.Child.Print(this)}}}";
                case SineFunction.COTANGENT:
                    return $"\\cot{{{node.Child.Print(this)}}}";
                default:
                    return null;
            }
        }

        /// <inheritdoc/>
        public override string Print(TensorNode node)
        {
            string cache = string.Empty;
            switch (node.TensorType)
            {
                case TensorType.Vector:
                    {
                        // Print each child seperated by ',' wrapped in "<>";
                        cache += "<";
                        for (int i = 0; i < node.ChildCount; i++)
                        {
                            cache += node.GetChild(i).Print(this);
                            if (i < node.ChildCount - 1)
                            {
                                cache += ",";
                            }
                        }
                        cache += ">";
                        return cache;
                    }
                case TensorType.Matrix:
                    {
                        cache = $"\\matrix[{node.SizeIdentity}{{";
                        for (int i = 0; i < node.ChildCount; i++)
                        {
                            cache += node.GetChild(i).Print(this);
                            if (i < node.ChildCount - 1)
                            {
                                cache += ",";
                            }
                        }
                        cache += "}";
                        return cache;
                    }
                default:
                    // TODO: Print matricies and tensors
                    return string.Empty;
            }
        }

        /// <inheritdoc/>
        public override string Print(VarValueNode node)
        {
            return $"{node.Character}";
        }
    }
}