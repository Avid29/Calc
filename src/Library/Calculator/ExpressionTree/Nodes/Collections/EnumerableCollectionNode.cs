using System.Collections.Generic;

namespace Calculator.ExpressionTree.Nodes.Collections
{
    public abstract class EnumerableCollectionNode : BranchNode
    {
        public EnumerableCollectionNode()
        {
            Children = new List<ExpNode>();
        }

        public EnumerableCollectionNode(EnumerableCollectionNode node)
        {
            Children = new List<ExpNode>();
            foreach (var child in node.Children)
            {
                Children.Add(child.Clone());
            }
        }

        protected List<ExpNode> Children { get; }

        public override int ChildCount => Children.Count;

        public override Priority Priority => Priority.OVERRIDE;

        public override void AddChild(ExpNode node)
        {
            Children.Add(node);
        }

        public override void InsertChild(BranchNode node)
        {
            ExpNode lastChild = Children[ChildCount - 1];
            Children.RemoveAt(ChildCount - 1);
            node.AddChild(lastChild);
            AddChild(node);
        }

        public override void ReplaceChild(ExpNode node, int index)
        {
            Children[index] = node;
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
