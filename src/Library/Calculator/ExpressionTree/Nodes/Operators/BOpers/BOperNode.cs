using Calculator.Exceptions.ExpressionTree;
using Calculator.ExpressionTree.Nodes.Values;
using System;

namespace Calculator.ExpressionTree.Nodes.Operators
{
    public abstract class BOperNode : OperNode
    {
        public BOperNode() { }

        protected BOperNode(BOperNode node)
        {
            LeftChild = node.LeftChild.Clone();
            RightChild = node.RightChild.Clone();
        }

        public ExpNode LeftChild { get; set; }

        public ExpNode RightChild { get; set; }

        public override int ChildCount
        {
            get
            {
                if (LeftChild == null) return 0;
                else if (RightChild == null) return 1;
                else return 2;
            }
        }

        public override void AddChild(ExpNode node)
        {
            if (LeftChild == null)
            {
                LeftChild = node;
            } else if (RightChild == null)
            {
                RightChild = node;
            } else
            {
                throw new BOperNodeAlreadyHasChildrenException(this);
            }

            node.Parent = this;
        }

        public override void InsertChild(BranchNode node)
        {
            ExpNode newGrandChild;
            if (RightChild != null)
            {
                newGrandChild = RightChild;
                RightChild = null;
            } else
            {
                // newGrandChild will be null if LeftChild is null.
                newGrandChild = LeftChild;
                LeftChild = null;
            }

            if (newGrandChild != null)
            {
                node.AddChild(newGrandChild);
            }

            AddChild(node);
        }

        public override void ReplaceChild(ExpNode node, int index)
        {
            switch (index)
            {
                case 0:
                    LeftChild = node;
                    break;
                case 1:
                    RightChild = node;
                    break;
                default:
                    throw new ArgumentOutOfRangeException($"{nameof(BOperNode)} only contains two (2) children. Zero (0) and one (1) are the only indicies.");
            }
        }

        public override ExpNode GetChild(int index)
        {
            switch (index)
            {
                case 0:
                    return LeftChild;
                case 1:
                    return RightChild;
                default:
                    throw new ArgumentOutOfRangeException($"{nameof(BOperNode)} only contains two (2) children. Zero (0) and one (1) are the only indicies.");
            }
        }

        public override void ClearChildren()
        {
            LeftChild = null;
            RightChild = null;
        }

        public override bool IsConstant()
        {
            return LeftChild.IsConstant() && RightChild.IsConstant();
        }

        public override bool IsConstantBy(VarValueNode variable)
        {
            return LeftChild.IsConstantBy(variable) && RightChild.IsConstantBy(variable);
        }
    }
}
