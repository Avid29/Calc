// Adam Dernis 2024

using Calculator.Exceptions.Simplification;
using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.ExpressionTree.Nodes.Operators;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.Functions;
using Calculator.ExpressionTree.Nodes.Operators.Functions.RowElim;
using Calculator.ExpressionTree.Nodes.Operators.Functions.VectorProduct;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SineNode;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Helpers;
using Calculator.Helpers.Simplification;
using Calculator.Operations.Abstract;
using Calculator.Operations.Groups.Tensors;
using System;

namespace Calculator.Operations;

/// <summary>
/// An <see cref="Operation"/> that simplifies expressions.
/// </summary>
public class Simplifier : Operation
{
    private readonly bool _safe;

    /// <summary>
    /// Initializes a new instance of the <see cref="Simplifier"/> class.
    /// </summary>
    /// <param name="safe">False if errors should be thrown.</param>
    public Simplifier(bool safe = true)
    {
        Error = null;
        _safe = safe;
    }

    /// <summary>
    /// Gets an error that occured during simplification.
    /// </summary>
    /// <remarks>
    /// Null if no errors occured.
    /// </remarks>
    public SimplificationException Error { get; private set; }

    /// <inheritdoc/>
    public override ExpNode Execute(AdditionOperNode node)
    {
        double valueProg = 0;

        // Simplify each child individually, and track the non-symbolic value summation progress.
        for (int i = 0; i < node.ChildCount; i++)
        {
            // Simplify the child
            ExpNode simpleChild = node.GetChild(i).Execute(this);

            switch (simpleChild)
            {
                // The simplified child is a raw numerical
                // Add to the summation value progress and remove the child
                case NumericalValueNode nvNode:
                    valueProg += nvNode.DoubleValue;
                    node.RemoveChild(i);
                    i--;
                    break;
                // The simplfied child is an addition operator
                // Add its children to the end of the current node for evaluation
                case AdditionOperNode aNode:
                    aNode.TransferChildren(node);
                    node.RemoveChild(i);
                    i--;
                    break;
                // The child is fully simplified (outside of ATerms analysis)
                // Replace the original child with the simplified child
                default:
                    node.ReplaceChild(simpleChild, i);
                    break;
            }
        }

        // If the numerical sum evaluation
        if (valueProg != 0 || node.ChildCount == 0)
        {
            node.AddChild(QuickOpers.MakeNumericalNode(valueProg));
        }

        // Simplify addition with additive term analysis
        AdditionHelpers.SimplfiyATerms(node);

        return node.ChildCount switch 
        {
            // There are no children, return a 0 numerical node
            0 => QuickOpers.MakeNumericalNode(0),

            // There's 1 child. Just return the child
            1 => node.GetChild(0),

            // Vector/Matrix/Tensor children would go unsimplified so far
            // Handle their summation
            _ => AdditionHelpers.SumTensors(node, this),
        };
    }

    /// <inheritdoc/>
    public override ExpNode Execute(DiffOperNode node)
    {
        // Define a differentiator and run it.
        // Simplify the child, differentiate it, then simplify again.
        Differentiator differentiator = new(node.Variable);
        return node.Child.Execute(this).Execute(differentiator).Execute(this);
    }

    /// <inheritdoc/>
    public override ExpNode Execute(ExpNode node) => node;

    /// <inheritdoc/>
    public override ExpNode Execute(RowElimOperNode node)
    {
        // Ensure matrix.
        if (node.Child is TensorNode tensorNode && tensorNode.TensorType == TensorType.Matrix)
        {
            MatrixByRow matrix = new(tensorNode);
            int[] leadingPositions = RefHelpers.GetLeadingColumns(matrix);

            // Put in row-echelon form
            for (int i = 0; i < matrix.Height; i++)
            {
                int leftMostCol = RefHelpers.GetLeftMostColumn(leadingPositions, i);
                matrix.SwapRows(i, leftMostCol);
                Common.Swap(ref leadingPositions[i], ref leadingPositions[leftMostCol]);

                if (leadingPositions[i] == -1) continue;

                matrix[i].MultiplyRow(QuickOpers.Reciprical(matrix[i][leadingPositions[i]]));
                for (int j = i + 1; j < matrix.Height; j++)
                {
                    matrix[j].AddRowToRow(matrix[i], QuickOpers.Negative(matrix[j][leadingPositions[i]]));
                    leadingPositions[j] = RefHelpers.GetLeadingColumn(matrix[j]);
                }
            }

            if (node.EliminationMethod == RowElimMethod.GaussJordan)
            {
                // Put in reduced row-echelon form
                for (int i = matrix.Height - 1; i > 0; i--)
                {
                    for (int j = i - 1; j >= 0; j--)
                    {
                        matrix[j].AddRowToRow(matrix[i], QuickOpers.Negative(matrix[j][leadingPositions[i]]));
                        leadingPositions[j] = RefHelpers.GetLeadingColumn(matrix[j]);
                    }
                }
            }

            return matrix.AsExpNode();
        }

        return HandleError(new CannotReduceNonMatrix(this, node.Child));
    }

    /// <inheritdoc/>
    public override ExpNode Execute(IntegralOperNode node)
    {
        Integrator integrator = new(node.Variable);
        return node.Child.Execute(this).Execute(integrator).Execute(this);
    }

    /// <inheritdoc/>
    public override ExpNode Execute(MultiplicationOperNode node)
    {
        double valueProg = 1;
        
        // Simplify each child individually, and track the non-symbolic value multiplication progress.
        for (int i = 0; i < node.ChildCount; i++)
        {
            // Simplify the child
            ExpNode simpleChild = node.GetChild(i).Execute(this);

            switch (simpleChild)
            {
                // The simplified child is a raw numerical
                // Add to the multiplicative value progress and remove the child
                case NumericalValueNode nvNode:
                    valueProg *= nvNode.DoubleValue;
                    node.RemoveChild(i);
                    i--;
                    break;
                // The simplfied child is a multiplication operator
                // Add its children to the end of the current node for evaluation
                case MultiplicationOperNode mNode:
                    mNode.TransferChildren(node);
                    node.RemoveChild(i);
                    i--;
                    break;
                // The child is fully simplified (outside of MTerms analysis)
                // Replace the original child with the simplified child
                default:
                    node.ReplaceChild(simpleChild, i);
                    break;
            }
        }

        // Anything multiplied by 0, is zero
        if (valueProg == 0)
        {
            return QuickOpers.MakeNumericalNode(0);
        }

        if (node.ChildCount == 0 || valueProg != 1)
        {
            node.AddChild(QuickOpers.MakeNumericalNode(valueProg));
        }

        MultiplicationHelpers.SimplfiyMTerms(node, this);

        switch (node.ChildCount)
        {
            case 0:
                return QuickOpers.MakeNumericalNode(0);
            case 1:
                return node.GetChild(0);
        }

        node = MultiplicationHelpers.MultiplyScalarTensor(node, this);

        if (node == null)
            return node;

        return MultiplicationHelpers.Distribute(node, this);
    }

    /// <inheritdoc/>
    public override ExpNode Execute(PowOperNode node)
    {
        // Simplify the left and right child and replace with the results.
        node.LeftChild = node.LeftChild.Execute(this);
        node.RightChild = node.RightChild.Execute(this);

        // Both the left and right handle child are numerical values.
        // Apply the power operation and return the result as a numerical value.
        if (node.LeftChild is NumericalValueNode lnvNode &&
            node.RightChild is NumericalValueNode rnvNode)
        {
            return QuickOpers.MakeNumericalNode(Math.Pow(lnvNode.DoubleValue, rnvNode.DoubleValue));
        }

        if (node.RightChild is IntValueNode ivNode)
        {
            // Handle simple exponents
            switch (ivNode.DoubleValue)
            {
                // The exponent is 0, return 1.
                case 0:
                    return QuickOpers.MakeNumericalNode(1);
                // The exponent is 1, return the base.
                case 1:
                    return node.LeftChild;
            }

            if (node.LeftChild is ValueNode)
            {
                // No good expanding
                return node;
            }

            int n = ivNode.Value;

            // Expand n times to multiplication
            MultiplicationOperNode mNode = new();
            mNode.AddChild(node.LeftChild);
            for (int i = 1; i < n; i++)
            {
                mNode.AddChild(node.LeftChild.Clone());
            }

            // Apply the multiplication
            return mNode.Execute(this);
        }

        return PowerHelpers.Distribute(node);
    }

    /// <inheritdoc/>
    public override ExpNode Execute(ParenthesisOperNode node)
    {
        // Remove Parenthesis if unnecessary
        // Either the parenthesis is the root node, the child is a value node,
        // or the parents priority is greater than the child's priority.
        if (node.IsRoot || node.Child is ValueNode ||
            node.Parent.Priority >= node.Child.Priority)
            return node.Child;

        return node;
    }

    /// <inheritdoc/>
    public override ExpNode Execute(RecipricalOperNode node)
    {
        // Simplify the child
        node.Child = node.Child.Execute(this);

        if (node.Child is NumericalValueNode nvNode)
        {
            return QuickOpers.MakeNumericalNode(1 / nvNode.DoubleValue);
        }

        return QuickOpers.Pow(node.Child, -1).Execute(this);
    }

    /// <inheritdoc/>
    public override ExpNode Execute(SignOperNode node)
    {
        node.Child = node.Child.Execute(this);
        return node.Sign switch
        {
            Sign.Positive => node.Child,
            Sign.Negative => QuickOpers.Multiply(-1, node.Child).Execute(this),
            _ => node,
        };
    }

    /// <inheritdoc/>
    public override ExpNode Execute(SineOperNode node)
    {
        node.Child = node.Child.Execute(this);

        if (node.Child is NumericalValueNode nvNode)
        {
            double value = node.SineFunction switch
            {
                SineFunction.Sine => Math.Sin(nvNode.DoubleValue),
                SineFunction.Cosine => Math.Cos(nvNode.DoubleValue),
                SineFunction.Tangent => Math.Tan(nvNode.DoubleValue),
                SineFunction.Cosecent => 1 / Math.Sin(nvNode.DoubleValue),
                SineFunction.Secant => 1 / Math.Cos(nvNode.DoubleValue),
                SineFunction.Cotangent => 1 / Math.Tan(nvNode.DoubleValue),
                _ => double.NaN,
            };

            return QuickOpers.MakeNumericalNode(value);
        }

        return node;
    }

    /// <inheritdoc/>
    public override ExpNode Execute(TensorNode node)
    {
        for (int i = 0; i < node.ChildCount; i++)
        {
            ExpNode simpleChild = node.GetChild(i).Execute(this);
            node.ReplaceChild(simpleChild, i);
        }

        return node;
    }

    /// <inheritdoc/>
    public override ExpNode Execute(VectorProductOperNode node)
    {
        // Verify left and right child are two multiplyable vectors. 
        if (node.LeftChild is not TensorNode vector1 || vector1.DimensionCount != 1 ||
            node.RightChild is not TensorNode vector2 || vector2.DimensionCount != 1 ||
            vector1.SizeIdentity != vector2.SizeIdentity)
            return HandleError(new CannotMultiplyTensors(this, node));

        int size = vector1.GetDimensionSize(1);
        switch (node.ProductMethod)
        {
            case VectorProductMethod.Dot:
                ExpNode[] terms = new ExpNode[size];
                for (int i = 0; i < size; i++)
                    terms[i] = QuickOpers.Multiply(vector1.GetChild(i), vector2.GetChild(i));
                return QuickOpers.Sum(terms).Execute(this);
            case VectorProductMethod.Cross: // TODO: Convert to matrix notation for determinant
            default:
                return node;
        }
    }

    /// <inheritdoc/>
    public override ExpNode Execute(VectorProjOperNode node)
    {
        if (!node.LeftChild.AreEqualSizeVectors(node.RightChild, out TensorNode a, out TensorNode b))
            return HandleError(new CannotVectorProject(this, node));

        VectorProductOperNode adotb = QuickOpers.DotProduct(a, (TensorNode)b.Clone());
        BOperNode bdotb = QuickOpers.DotProduct((TensorNode)b.Clone(), (TensorNode)b.Clone());
        return QuickOpers.Multiply(b, adotb, QuickOpers.Reciprical(bdotb)).Execute(this);
    }

    /// <summary>
    /// Puts the simplifier in an error state and returns <see langword="null"/>.
    /// </summary>
    /// <param name="exception">The exception type.</param>
    /// <returns><see langword="null"/>.</returns>
    public ExpNode HandleError(SimplificationException exception)
    {
        Error = exception;
        if (!_safe) throw exception;
        return null;
    }
}
