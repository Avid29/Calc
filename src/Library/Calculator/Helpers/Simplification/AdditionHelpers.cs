// Adam Dernis © 2021

using Calculator.Exceptions.Simplification;
using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.Operations;
using Calculator.Operations.Groups.Terms;
using System.Collections.Generic;

namespace Calculator.Helpers.Simplification
{
    /// <summary>
    /// A class containing methods for helping with additon simplification.
    /// </summary>
    public static class AdditionHelpers
    {
        /// <summary>
        /// Splits an <see cref="AdditionOperNode"/> into terms and simplifies by common terms.
        /// </summary>
        /// <param name="node">The <see cref="AdditionOperNode"/> to simplify.</param>
        /// <returns>The resulting <see cref="ExpNode"/>.</returns>
        public static AdditionOperNode SimplfiyATerms(AdditionOperNode node)
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

        /// <summary>
        /// Adds tensors.
        /// </summary>
        /// <param name="node">The <see cref="AdditionOperNode"/> containing tensors.</param>
        /// <param name="simplifier">The <see cref="Simplifier"/> calling.</param>
        /// <returns>The resuling <see cref="ExpNode"/>.</returns>
        public static ExpNode SumTensors(AdditionOperNode node, Simplifier simplifier)
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
                                ExpNode addedNode = QuickOpers
                                    .Sum(tensorNode.GetChild(j), otherTensorNode.GetChild(j))
                                    .Execute(simplifier);
                                tensorNode.ReplaceChild(addedNode, j);
                            }
                        }
                        else return simplifier.HandleError(new CannotAddTensors(simplifier, node, $"Cannot add tensor of shape {otherTensorNode.SizeIdentity} and tensor of shape {tensorNode.SizeIdentity}."));
                    }
                    else return simplifier.HandleError(new CannotAddTensors(simplifier, node, "Cannot add scalar and tensor."));
                }

                return tensorNode;
            }
            else
            {
                // There is a scalar.
                // There cannot be any tensors
                for (int i = 1; i < node.ChildCount; i++)
                {
                    if (node.GetChild(i) is TensorNode) return simplifier.HandleError(new CannotAddTensors(simplifier, node, "Cannot add tensor and scalar."));
                }
            }

            return node;
        }
    }
}
