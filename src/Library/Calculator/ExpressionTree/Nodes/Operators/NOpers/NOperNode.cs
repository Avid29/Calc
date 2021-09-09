// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Values;
using System.Collections.Generic;

namespace Calculator.ExpressionTree.Nodes.Operators
{
    public abstract class NOperNode : OperNode
    {
        public NOperNode()
        {
            Children = new List<ExpNode>();
        }

        protected NOperNode(NOperNode node)
        {
            Children = new List<ExpNode>();
            foreach (var child in node.Children)
            {
                Children.Add(child.Clone());
            }
        }

        public override int ChildCount => Children.Count;

        protected List<ExpNode> Children { get; }

        public static NOperNode MakeNOperNode(char c)
        {
            switch (c)
            {
                case '+':
                case '-':
                    return new AdditionOperNode();
                case '*':
                case '/':
                    return new MultiplicationOperNode();
                default:
                    return null;
            }
        }

        public override void AddChild(ExpNode node)
        {
            Children.Add(node);
            node.Parent = this;
        }

        public void AddChildAt(ExpNode node, int index)
        {
            Children.Insert(index, node);
        }

        public override void ReplaceChild(ExpNode node, int index)
        {
            Children[index] = node;
        }

        public override void InsertChild(BranchNode node)
        {
            ExpNode lastChild = Children[ChildCount - 1];
            Children.RemoveAt(ChildCount - 1);
            node.AddChild(lastChild);
            AddChild(node);
        }

        public void RemoveChild(int index)
        {
            Children.RemoveAt(index);
        }

        public override ExpNode GetChild(int index)
        {
            return Children[index];
        }

        public override void ClearChildren()
        {
            Children.Clear();
        }

        public void TransferChildren(NOperNode node)
        {
            foreach (var child in Children)
            {
                node.AddChild(child);
            }
        }

        public override bool IsConstant()
        {
            foreach (var child in Children)
            {
                if (!child.IsConstant()) return false;
            }
            return true;
        }

        public override bool IsConstantBy(VarValueNode variable)
        {
            foreach (var child in Children)
            {
                if (!child.IsConstantBy(variable)) return false;
            }
            return true;
        }
    }
}
