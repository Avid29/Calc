using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.ExpressionTree.Terms;
using Calculator.Operations.Abstract;
using System;
using System.Collections.Generic;

namespace Calculator.Operations
{
    public class Simplifier : Operation
    {
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
            }

            if (node.ChildCount == 0 || valueProg != 0) node.AddChild(Helpers.MakeValueNode(valueProg));

            SimplfiyATerms(node);
            
            if (node.ChildCount == 0)
            {
                return Helpers.MakeValueNode(0);
            }
            else if (node.ChildCount == 1)
            {
                return node.GetChild(0);
            }

            // TODO: Tensor addition

            return node;
        }

        public override ExpNode Execute(ExpNode node)
        {
            return node;
        }

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
                }
            }

            // Anything multiplied by 0, is zero
            if (valueProg == 0) return Helpers.MakeValueNode(0);

            if (node.ChildCount == 0 || valueProg != 1) node.AddChild(Helpers.MakeValueNode(valueProg));

            SimplfiyMTerms(node);

            if (node.ChildCount == 0)
            {
                return Helpers.MakeValueNode(0);
            }
            else if (node.ChildCount == 1)
            {
                return node.GetChild(0);
            }

            return Distribute(node);
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
            SortedSet<AdditiveTerm> aTerms = new SortedSet<AdditiveTerm>();

            for (int i = 0; i < node.ChildCount; i++)
            {
                AdditiveTerm aTerm = new AdditiveTerm(node.GetChild(i));
                AdditiveTerm existingATerm;

                if (aTerms.TryGetValue(aTerm, out existingATerm))
                {
                    existingATerm.AddToCoefficient(aTerm);
                } else
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
            SortedSet<MultiplicativeTerm> mTerms = new SortedSet<MultiplicativeTerm>();

            for (int i = 0; i < node.ChildCount; i++)
            {
                MultiplicativeTerm mTerm = new MultiplicativeTerm(node.GetChild(i));
                MultiplicativeTerm existingMTerm;

                if (mTerms.TryGetValue(mTerm, out existingMTerm))
                {
                    existingMTerm.AddToExponent(mTerm, this);
                } else
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
            if (node.GetChild(node.ChildCount-1) is ParenthesisOperNode parNode)
            {
                // Last child is parenthesis
                if (parNode.Child is AdditionOperNode aNode)
                {
                    // Last grandchild is addition
                    for (int i = 0; i < aNode.ChildCount; i++)
                    {
                        MultiplicationOperNode mNode = new MultiplicationOperNode();
                        mNode.AddChild(aNode.GetChild(i));
                        for (int j = 0; j < node.ChildCount-1; j++)
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
                        PowOperNode pow = new PowOperNode();
                        pow.LeftChild = mNode.GetChild(i);
                        pow.RightChild = node.RightChild.Clone();
                        mNode.ReplaceChild(pow, i);
                    }
                    return mNode;
                }
            }
            return node;
        }
    }
}
