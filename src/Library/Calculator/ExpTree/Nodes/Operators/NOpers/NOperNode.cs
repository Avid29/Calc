using System.Collections.Generic;

namespace Calculator.ExpTree.Nodes.Operators
{
    public abstract class NOperNode : OperNode
    {
        protected List<ExpNode> Children { get; }

        public override int ChildCount => Children.Count;

        public override void AddChild(ExpNode node)
        {
            Children.Add(node);
            node.Parent = this;
        }

        public void AddChildAt(ExpNode node, int index)
        {
            Children.Insert(index, node);
        }

        public override void InsertChild(BranchNode node)
        {
            ExpNode lastChild = Children[ChildCount - 1];
            Children.RemoveAt(ChildCount - 1);
            node.AddChild(lastChild);
            AddChild(node);
        }

        public override ExpNode GetChild(int index)
        {
            return Children[index];
        }

        public override void ClearChildren()
        {
            Children.Clear();
        }
    }
}
