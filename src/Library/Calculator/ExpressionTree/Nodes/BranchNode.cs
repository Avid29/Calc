// Adam Dernis © 2021

namespace Calculator.ExpressionTree.Nodes
{
    /// <summary>
    /// A <see cref="ExpNode"/> containing children.
    /// </summary>
    public abstract class BranchNode : ExpNode
    {
        /// <summary>
        /// Gets the number of children in the <see cref="BranchNode"/>.
        /// </summary>
        public abstract int ChildCount { get; }

        /// <summary>
        /// Adds a child to the <see cref="BranchNode"/>.
        /// </summary>
        /// <param name="node">The child to add.</param>
        public abstract void AddChild(ExpNode node);

        /// <summary>
        /// Inserts a child between this <see cref="BranchNode"/> and its last child.
        /// </summary>
        /// <param name="node">The node to insert.</param>
        public abstract void InsertChild(BranchNode node);

        /// <summary>
        /// Replaces a child at an index with a different <see cref="ExpNode"/> child.
        /// </summary>
        /// <param name="node">The new <see cref="ExpNode"/> child.</param>
        /// <param name="index">The index of the child to replace.</param>
        public abstract void ReplaceChild(ExpNode node, int index);

        /// <summary>
        /// Gets the child at <paramref name="index"/> in this <see cref="BranchNode"/>.
        /// </summary>
        /// <param name="index">The index of the child to return.</param>
        /// <returns>The child at <paramref name="index"/> in this <see cref="BranchNode"/>.</returns>
        public abstract ExpNode GetChild(int index);

        /// <summary>
        /// Removes all children from this <see cref="BranchNode"/>.
        /// </summary>
        public abstract void ClearChildren();
    }
}
