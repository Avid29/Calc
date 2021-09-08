using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Operations.Abstract;
using System;

namespace Calculator.Operations
{
    public class Simplifier : Operation
    {
        public override ExpNode Execute(ExpNode node)
        {
            return node;
        }

        public override ExpNode Execute(PowOperNode node)
        {
            node.LeftChild = node.LeftChild.Execute(this);
            node.RightChild = node.RightChild.Execute(this);

            if (node.LeftChild is NumericalValueNode lnvNode && node.RightChild is NumericalValueNode rnvNode)
            {
                return Helpers.MakeValueNode(Math.Pow(lnvNode.DoubleValue, rnvNode.DoubleValue));
            }

            if (node.RightChild is IntValueNode ivNode)
            {
                if (node.LeftChild is ValueNode)
                {
                    // No good expanding
                    return node;
                }
                
                int n = ivNode.Value;
                // Expand n times
                MultiplicationOperNode mNode = new MultiplicationOperNode();

                mNode.AddChild(node.LeftChild);
                for (int i = 1; i < n; i++)
                {
                    mNode.AddChild(node.LeftChild.Clone());
                }

                return mNode.Execute(this);
            }

            return Distribute(node);
        }

        public override ExpNode Execute(ParenthesisOperNode node)
        {
            return node.Child;
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
                        PowOperNode pow = new PowOperNode();
                        pow.LeftChild = mNode.GetChild(i);
                        pow.RightChild = node.RightChild.Clone();
                        mNode.ReplaceChildAt(pow, i);
                    }
                    return mNode;
                }
            }
            return node;
        }
    }
}
