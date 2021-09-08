using Calculator.Exceptions.ExpressionTree;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpressionTree.Nodes.Values;
using System;

namespace Calculator.ExpressionTree.Nodes.Operators
{
    public abstract class UOperNode : OperNode
    {
        public UOperNode() { }

        protected UOperNode(UOperNode node)
        {
            Child = node.Child;
        }

        public ExpNode Child { get; set; }

        public override int ChildCount => Child == null ? 0 : 1;

        public static UOperNode MakeUOperNode(char c)
        {
            switch (c)
            {
                case '+':
                case '-':
                    return new SignOperNode(c);
                case '/':
                    return new RecipricalOperNode();
                default:
                    return null;
            }
        }

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

            AddChild(node, true);
        }

        public override void ReplaceChild(ExpNode node, int index)
        {
            if (index == 0)
            {
                Child = node;
            }
            else
            {
                throw new ArgumentOutOfRangeException($"{nameof(UOperNode)} only contains one (1) child. Zero (0) is the only index.");
            }
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

        public override bool IsConstant()
        {
            return Child.IsConstant();
        }

        public override bool IsConstantBy(VarValueNode variable)
        {
            return Child.IsConstantBy(variable);
        }
    }
}
