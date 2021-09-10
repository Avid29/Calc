// Adam Dernis © 2021

using Calculator.Exceptions.Simplification;
using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.Functions;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SineNode;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.ExpressionTree.Terms;
using Calculator.Operations.Abstract;
using System;
using System.Collections.Generic;

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

            if (node.ChildCount == 0 || valueProg != 0) node.AddChild(Helpers.MakeNumericalNode(valueProg));

            SimplfiyATerms(node);

            if (node.ChildCount == 0)
            {
                return Helpers.MakeNumericalNode(0);
            }
            else if (node.ChildCount == 1)
            {
                return node.GetChild(0);
            }

            return SumTensors(node);
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
            if (valueProg == 0) return Helpers.MakeNumericalNode(0);

            if (node.ChildCount == 0 || valueProg != 1) node.AddChild(Helpers.MakeNumericalNode(valueProg));

            SimplfiyMTerms(node);

            if (node.ChildCount == 0)
            {
                return Helpers.MakeNumericalNode(0);
            }
            else if (node.ChildCount == 1)
            {
                return node.GetChild(0);
            }

            node = MultiplyScalarTensor(node);

            if (node == null) return node;

            return Distribute(node);
        }

        /// <inheritdoc/>
        public override ExpNode Execute(PowOperNode node)
        {
            node.LeftChild = node.LeftChild.Execute(this);
            node.RightChild = node.RightChild.Execute(this);

            if (node.LeftChild is NumericalValueNode lnvNode && node.RightChild is NumericalValueNode rnvNode)
            {
                return Helpers.MakeNumericalNode(Math.Pow(lnvNode.DoubleValue, rnvNode.DoubleValue));
            }

            if (node.RightChild is IntValueNode ivNode)
            {
                if (ivNode.DoubleValue == 0) return Helpers.MakeNumericalNode(1);
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

            return Distribute(node);
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
                return Helpers.MakeNumericalNode(1 / nvNode.DoubleValue);
            }

            return Helpers.Pow(node.Child, -1).Execute(this);
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
                            return Helpers.MakeNumericalNode(nvNode.DoubleValue * -1);
                        }

                        return Helpers.Multiply(-1, node.Child);
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

                return Helpers.MakeNumericalNode(value);
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

        private AdditionOperNode SimplfiyATerms(AdditionOperNode node)
        {
            SortedSet<AdditiveTerm> aTerms = new();

            for (int i = 0; i < node.ChildCount; i++)
            {
                AdditiveTerm aTerm = new(node.GetChild(i));

                if (aTerms.TryGetValue(aTerm, out AdditiveTerm existingATerm))
                {
                    existingATerm.AddToCoefficient(aTerm);
                }
                else
                {
                    aTerms.Add(aTerm);
                }
            }

            node.ClearChildren();
            foreach (var term in aTerms)
            {
                node.AddChild(term.AsExpNode());
            }

            return node;
        }

        private MultiplicationOperNode SimplfiyMTerms(MultiplicationOperNode node)
        {
            SortedSet<MultiplicativeTerm> mTerms = new();

            for (int i = 0; i < node.ChildCount; i++)
            {
                MultiplicativeTerm mTerm = new(node.GetChild(i));

                if (mTerms.TryGetValue(mTerm, out MultiplicativeTerm existingMTerm))
                {
                    existingMTerm.AddToExponent(mTerm, this);
                }
                else
                {
                    mTerms.Add(mTerm);
                }
            }

            node.ClearChildren();
            foreach (var term in mTerms)
            {
                node.AddChild(term.AsExpNode());
            }

            return node;
        }

        private ExpNode Distribute(MultiplicationOperNode node)
        {
            if (node.GetChild(node.ChildCount - 1) is ParenthesisOperNode parNode)
            {
                // Last child is parenthesis
                if (parNode.Child is AdditionOperNode aNode)
                {
                    // Last grandchild is addition
                    for (int i = 0; i < aNode.ChildCount; i++)
                    {
                        MultiplicationOperNode mNode = new();
                        mNode.AddChild(aNode.GetChild(i));
                        for (int j = 0; j < node.ChildCount - 1; j++)
                        {
                            mNode.AddChild(node.GetChild(j).Clone());
                        }

                        aNode.ReplaceChild(mNode, i);
                    }

                    return aNode.Execute(this);
                }
            }

            return node;
        }

        private ExpNode Distribute(PowOperNode node)
        {
            if (node.LeftChild is ParenthesisOperNode parNode)
            {
                // Child is parenthesis
                // Check for multiplication
                if (parNode.Child is MultiplicationOperNode mNode)
                {
                    // Grand child is multiplication
                    // Distribute
                    for (int i = 0; i < mNode.ChildCount; i++)
                    {
                        PowOperNode pow = Helpers.Pow(mNode.GetChild(i), node.RightChild.Clone());
                        mNode.ReplaceChild(pow, i);
                    }
                    return mNode;
                }
            }
            return node;
        }

        private ExpNode SumTensors(AdditionOperNode node)
        {
            if (node.GetChild(0) is TensorNode tensorNode)
            {
                for (int i = 1; i < node.ChildCount; i++)
                {
                    if (node.GetChild(i) is TensorNode otherTensorNode)
                    {
                        if (otherTensorNode.SizeIdentity == tensorNode.SizeIdentity)
                        {
                            for (int j = 0; j < tensorNode.ChildCount; j++)
                            {
                                ExpNode addedNode = Helpers
                                    .Sum(tensorNode.GetChild(j), otherTensorNode.GetChild(j))
                                    .Execute(this);
                                tensorNode.ReplaceChild(addedNode, j);
                            }
                        }
                        else return HandleError(new CannotAddTensors(this, node, $"Cannot add tensor of shape {otherTensorNode.SizeIdentity} and tensor of shape {tensorNode.SizeIdentity}."));
                    }
                    else return HandleError(new CannotAddTensors(this, node, "Cannot add scalar and tensor."));
                }

                return tensorNode;
            }
            else
            {
                // There is a scalar.
                // There cannot be any tensors
                for (int i = 1; i < node.ChildCount; i++)
                {
                    if (node.GetChild(i) is TensorNode) return HandleError(new CannotAddTensors(this, node, "Cannot add tensor and scalar."));
                }
            }

            return node;
        }

        /// <remarks>
        /// Multiplies a tensor by scalars.
        /// </remarks>
        private MultiplicationOperNode MultiplyScalarTensor(MultiplicationOperNode node)
        {
            TensorNode tensor1 = null;
            int ti = -1;

            for (int i = 0; i < node.ChildCount; i++)
            {
                if (i == ti) continue;

                if (node.GetChild(i) is TensorNode tensor2)
                {
                    if (tensor1 != null)
                    {
                        if (i < ti)
                        {
                            TensorNode swap = tensor1;
                            tensor1 = tensor2;
                            tensor2 = swap;
                        }

                        if (!tensor1.CanMatrixMultiply(tensor2)) return (MultiplicationOperNode)HandleError(new CannotMultiplyTensors(this, node, $"Tensor nodes of size {tensor1.SizeIdentity} and {tensor2.SizeIdentity} could not be multiplied."));
                    } else
                    {
                        tensor1 = tensor2;
                        ti = i;
                        i = -1;
                    }
                }
                else
                {
                    if (tensor1 != null)
                    {
                        for (int j = 0; j < tensor1.ChildCount; j++)
                        {
                            ExpNode simpleChild = Helpers.Multiply(tensor1.GetChild(j), node.GetChild(i)).Execute(this);
                            tensor1.ReplaceChild(simpleChild, j);
                        }

                        node.RemoveChild(i);
                        if (i < ti) ti--;
                        i--;
                    }
                }
            }

            return node;
        }

        private ExpNode HandleError(SimplificationException exception)
        {
            Error = exception;
            if (!_safe) throw exception;
            return null;
        }
    }
}