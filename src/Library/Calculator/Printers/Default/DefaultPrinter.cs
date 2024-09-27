// Adam Dernis 2024

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.Functions;
using Calculator.ExpressionTree.Nodes.Operators.Functions.RowElim;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SineNode;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Printers.Abstract;

namespace Calculator.Printers.Default;

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
    public override string Print(ExpNode node) => string.Empty;

    /// <inheritdoc/>
    public override string Print(DiffOperNode node) => $"\\diff[{node.Variable.Print(this)}]{{{node.Child.Print(this)}}}";

    /// <inheritdoc/>
    public override string Print(FloatValueNode node) => $"{node.Value}";

    /// <inheritdoc/>
    public override string Print(RowElimOperNode node)
    {
        string cache = node.EliminationMethod switch
        {
            RowElimMethod.Gauss => @"\\ref",
            RowElimMethod.GaussJordan => @"\\rref",
            _ => string.Empty,
        };

        return $"{cache}{{{node.Child.Print(this)}}}";
    }

    /// <inheritdoc/>
    public override string Print(IntegralOperNode node)
    {
        if (node.IsDeterminate)
        {
            return $"\\int[{node.Variable.Print(this)}, {node.LowerBound.Print(this)}, {node.UpperBound.Print(this)}]{{{node.Child.Print(this)}}}";
        }
        else
        {
            return $"\\int[{node.Variable.Print(this)}]{{{node.Child.Print(this)}}}";
        }
    }

    /// <inheritdoc/>
    public override string Print(IntValueNode node) => $"{node.Value}";

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
    public override string Print(ParenthesisOperNode node) => $"({node.Child.Print(this)})";

    /// <inheritdoc/>
    public override string Print(PowOperNode node) => $"{node.LeftChild.Print(this)}^{node.RightChild.Print(this)}";

    /// <inheritdoc/>
    public override string Print(SignOperNode node)
    {
        return node.Sign switch
        {
            Sign.Positive => $"+{node.Child.Print(this)}",
            Sign.Negative => $"-{node.Child.Print(this)}",
            _ => node.Child.Print(this),
        };
    }

    /// <inheritdoc/>
    public override string Print(SineOperNode node)
    {
        return node.SineFunction switch
        {
            SineFunction.Sine => $"\\sin{{{node.Child.Print(this)}}}",
            SineFunction.Cosine => $"\\cos{{{node.Child.Print(this)}}}",
            SineFunction.Tangent => $"\\tan{{{node.Child.Print(this)}}}",
            SineFunction.Cosecent => $"\\csc{{{node.Child.Print(this)}}}",
            SineFunction.Secant => $"\\sec{{{node.Child.Print(this)}}}",
            SineFunction.Cotangent => $"\\cot{{{node.Child.Print(this)}}}",
            _ => null,
        };
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
                    cache = $"\\matrix{node.SizeIdentity}{{";
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
                // TODO: Print tensors
                return string.Empty;
        }
    }

    /// <inheritdoc/>
    public override string Print(VarValueNode node) => $"{node.Character}";
}
