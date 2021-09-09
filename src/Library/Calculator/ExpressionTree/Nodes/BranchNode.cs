// Adam Dernis © 2021

namespace Calculator.ExpressionTree.Nodes
{
    public abstract class BranchNode : ExpNode
    {
        public abstract int ChildCount { get; }

        public abstract void AddChild(ExpNode node);

        public abstract void InsertChild(BranchNode node);

        public abstract void ReplaceChild(ExpNode node, int index);

        public abstract ExpNode GetChild(int index);

        public abstract void ClearChildren();
    }
}
