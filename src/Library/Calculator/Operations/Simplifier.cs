// Adam Dernis © 2021

using Calculator.Exceptions.Simplification;
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
using Calculator.Helpers;
using Calculator.Helpers.Simplification;
using Calculator.Operations.Abstract;
using Calculator.Operations.Groups.Tensors;
using System;

namespace Calculator.Operations
{
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

            for (int i = 0; i < node.ChildCount; i++)
            {
                ExpNode simpleChild = node.GetChild(i).Execute(this);

                if (simpleChild is NumericalValueNode nvNode)
                {
                    valueProg += nvNode.DoubleValue;
                    node.RemoveChild(i);
                    i--;
                }
                else if (simpleChild is AdditionOperNode aNode)
                {
                    aNode.TransferChildren(node);
                    node.RemoveChild(i);
                    i--;
                }
                else
                {
                    node.ReplaceChild(simpleChild, i);
                }
            }

            if (node.ChildCount == 0 || valueProg != 0) node.AddChild(QuickOpers.MakeNumericalNode(valueProg));

            AdditionHelpers.SimplfiyATerms(node);

            if (node.ChildCount == 0)
            {
                return QuickOpers.MakeNumericalNode(0);
            }
            else if (node.ChildCount == 1)
            {
                return node.GetChild(0);
            }

            return AdditionHelpers.SumTensors(node, this);
        }

        /// <inheritdoc/>
        public override ExpNode Execute(DiffOperNode node)
        {
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
                MatrixByRow matrix = new MatrixByRow(tensorNode);
                int[] leadingPositions = RefHelpers.GetLeadingColumns(matrix);

                // Put in row-echelon form
                for (int i = 0; i < matrix.Height; i++)
                {
                    int leftMostCol = RefHelpers.GetLeftMostColumn(leadingPositions, i);
                    matrix.SwapRows(i, leftMostCol);
                    Common.Swap(ref leadingPositions[i], ref leadingPositions[leftMostCol]);

                    if (leadingPositions[i] == -1)
                        continue;

                    matrix[i].MultiplyRow(QuickOpers.Reciprical(matrix[i][leadingPositions[i]]));
                    for (int j = i+1; j < matrix.Height; j++)
                    {
                        matrix[j].AddRowToRow(matrix[i], QuickOpers.Negative(matrix[j][leadingPositions[i]]));
                        leadingPositions[j] = RefHelpers.GetLeadingColumn(matrix[j]);
                    }
                }

                if (node.EliminationMethod == RowElimMethod.GaussJordan)
                {
                    // Put in reduced row-echelon form
                    for (int i = matrix.Height-1; i > 0; i--)
                    {
                        for (int j = i-1; j >= 0; j--)
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

            for (int i = 0; i < node.ChildCount; i++)
            {
                ExpNode simpleChild = node.GetChild(i).Execute(this);

                if (simpleChild is NumericalValueNode nvNode)
                {
                    valueProg *= nvNode.DoubleValue;
                    node.RemoveChild(i);
                    i--;
                } else if (simpleChild is MultiplicationOperNode mNode)
                {
                    mNode.TransferChildren(node);
                    node.RemoveChild(i);
                    i--;
                } else
                {
                    node.ReplaceChild(simpleChild, i);
                }
            }

            // Anything multiplied by 0, is zero
            if (valueProg == 0) return QuickOpers.MakeNumericalNode(0);

            if (node.ChildCount == 0 || valueProg != 1) node.AddChild(QuickOpers.MakeNumericalNode(valueProg));

            MultiplicationHelpers.SimplfiyMTerms(node, this);

            if (node.ChildCount == 0)
            {
                return QuickOpers.MakeNumericalNode(0);
            }
            else if (node.ChildCount == 1)
            {
                return node.GetChild(0);
            }

            node = MultiplicationHelpers.MultiplyScalarTensor(node, this);

            if (node == null) return node;

            return MultiplicationHelpers.Distribute(node, this);
        }

        /// <inheritdoc/>
        public override ExpNode Execute(PowOperNode node)
        {
            node.LeftChild = node.LeftChild.Execute(this);
            node.RightChild = node.RightChild.Execute(this);

            if (node.LeftChild is NumericalValueNode lnvNode && node.RightChild is NumericalValueNode rnvNode)
            {
                return QuickOpers.MakeNumericalNode(Math.Pow(lnvNode.DoubleValue, rnvNode.DoubleValue));
            }

            if (node.RightChild is IntValueNode ivNode)
            {
                if (ivNode.DoubleValue == 0) return QuickOpers.MakeNumericalNode(1);
                if (ivNode.DoubleValue == 1) return node.LeftChild;

                if (node.LeftChild is ValueNode)
                {
                    // No good expanding
                    return node;
                }

                int n = ivNode.Value;
                // Expand n times
                MultiplicationOperNode mNode = new();

                mNode.AddChild(node.LeftChild);
                for (int i = 1; i < n; i++)
                {
                    mNode.AddChild(node.LeftChild.Clone());
                }

                return mNode.Execute(this);
            }

            return PowerHelpers.Distribute(node);
        }

        /// <inheritdoc/>
        public override ExpNode Execute(ParenthesisOperNode node)
        {
            // Remove Parenthesis if unnecessary
            if (node.Child is ValueNode || node.IsRoot || node.Parent.Priority >= node.Child.Priority) return node.Child;
            return node;
        }

        /// <inheritdoc/>
        public override ExpNode Execute(RecipricalOperNode node)
        {
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
            switch (node.Sign)
            {
                case Sign.POSITIVE:
                    return node.Child;
                case Sign.NEGATIVE:
                    {
                        if (node.Child is NumericalValueNode nvNode)
                        {
                            return QuickOpers.MakeNumericalNode(nvNode.DoubleValue * -1);
                        }

                        return QuickOpers.Multiply(-1, node.Child).Execute(this);
                    }
                default:
                    return node;
            }
        }

        /// <inheritdoc/>
        public override ExpNode Execute(SineOperNode node)
        {
            node.Child = node.Child.Execute(this);

            if (node.Child is NumericalValueNode nvNode)
            {
                double value = 0;
                switch (node.SineFunction)
                {
                    case SineFunction.SINE:
                        value = Math.Sin(nvNode.DoubleValue);
                        break;
                    case SineFunction.COSINE:
                        value = Math.Cos(nvNode.DoubleValue);
                        break;
                    case SineFunction.TANGENT:
                        value = Math.Tan(nvNode.DoubleValue);
                        break;
                    case SineFunction.COSECANT:
                        value = 1 / Math.Sin(nvNode.DoubleValue);
                        break;
                    case SineFunction.SECANT:
                        value = 1 / Math.Cos(nvNode.DoubleValue);
                        break;
                    case SineFunction.COTANGENT:
                        value = 1 / Math.Tan(nvNode.DoubleValue);
                        break;
                }

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
}
