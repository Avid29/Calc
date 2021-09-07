using Calculator.Exceptions.ExpTree;
using System;

namespace Calculator.ExpTree.Nodes.Operators
{
    public abstract class UOperNode : OperNode
    {
        public ExpNode Child { get; protected set; }

        public override int ChildCount => Child == null ? 0 : 1;

        public override void AddChild(ExpNode node)
        {
            AddChild(node);
        }

        public void AddChild(ExpNode node, bool overwrite = false)
        {
            if (Child == null || overwrite)
            {
                Child = node;
            } else
            {
                throw new UOperNodeAlreadyHasChildException(this);
            }

            node.Parent = this;
        }

        public override void InsertChild(BranchNode node)
        {
            if (Child != null)
            {
                node.AddChild(Child);
            }

            AddChild(node);
        }

        public override ExpNode GetChild(int index = 0)
        {
            if (index == 0)
            {
                return Child;
            } else
            {
                throw new ArgumentOutOfRangeException($"{nameof(UOperNode)} only contains one (1) child. Zero (0) is the only index.");
            }
        }

        public override void ClearChildren()
        {
            Child = null;
        }

        public bool HasChild()
        {
            return Child != null;
        }
    }
}
