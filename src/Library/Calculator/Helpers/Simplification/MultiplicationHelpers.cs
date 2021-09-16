// Adam Dernis © 2021

using Calculator.Exceptions.Simplification;
using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.Operations;
using Calculator.Operations.Groups.Terms;
using System.Collections.Generic;

namespace Calculator.Helpers.Simplification
{
    /// <summary>
    /// A class containing methods for helping with multiplication simplification.
    /// </summary>
    public static class MultiplicationHelpers
    {
        /// <summary>
        /// Splits an <see cref="MultiplicationOperNode"/> into terms and simplifies by common terms.
        /// </summary>
        /// <param name="node">The <see cref="MultiplicationOperNode"/> to simplify.</param>
        /// <param name="simplifier">The <see cref="Simplifier"/> calling.</param>
        /// <returns>The resulting <see cref="ExpNode"/>.</returns>
        public static MultiplicationOperNode SimplfiyMTerms(MultiplicationOperNode node, Simplifier simplifier)
        {
            SortedSet<MultiplicativeTerm> mTerms = new();

            for (int i = 0; i < node.ChildCount; i++)
            {
                MultiplicativeTerm mTerm = new(node.GetChild(i));

                if (mTerms.TryGetValue(mTerm, out MultiplicativeTerm existingMTerm))
                {
                    existingMTerm.AddToExponent(mTerm, simplifier);
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

        /// <summary>
        /// Applies the multiplicative distributive property.
        /// </summary>
        /// <param name="node">The <see cref="MultiplicationOperNode"/> to simplify.</param>
        /// <param name="simplifier">The <see cref="Simplifier"/> calling.</param>
        /// <returns>The resuling <see cref="ExpNode"/>.</returns>
        public static ExpNode Distribute(MultiplicationOperNode node, Simplifier simplifier)
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

                    return aNode.Execute(simplifier);
                }
            }

            return node;
        }

        /// <summary>
        /// Multiplies a tensor by scalars.
        /// </summary>
        /// <param name="node">The <see cref="MultiplicationOperNode"/> to simplify.</param>
        /// <param name="simplifier">The <see cref="Simplifier"/> calling.</param>
        /// <returns>The resuling <see cref="MultiplicationOperNode"/>.</returns>
        public static MultiplicationOperNode MultiplyScalarTensor(MultiplicationOperNode node, Simplifier simplifier)
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

                        if (!tensor1.CanMatrixMultiply(tensor2)) return (MultiplicationOperNode)simplifier.HandleError(new CannotMultiplyTensors(simplifier, node, $"Tensor nodes of size {tensor1.SizeIdentity} and {tensor2.SizeIdentity} could not be multiplied."));
                    }
                    else
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
                            ExpNode simpleChild = QuickOpers.Multiply(tensor1.GetChild(j), node.GetChild(i)).Execute(simplifier);
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
    }
}
