// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Operators;
using Calculator.ExpressionTree.Nodes.Values;
using System.Collections.Generic;

namespace Calculator.ExpressionTree.Nodes.Collections
{
    /// <summary>
    /// A base class for <see cref="BranchNode"/>s that contain a set of values and are not an <see cref="OperNode"/>.
    /// </summary>
    public abstract class EnumerableCollectionNode : BranchNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="EnumerableCollectionNode"/> class.
        /// </summary>
        public EnumerableCollectionNode()
        {
            Children = new List<ExpNode>();
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="EnumerableCollectionNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="EnumerableCollectionNode"/> to clone.</param>
        protected EnumerableCollectionNode(EnumerableCollectionNode node)
        {
            Children = new List<ExpNode>();
            foreach (var child in node.Children)
            {
                Children.Add(child.Clone());
            }
        }

        /// <inheritdoc/>
        public override int ChildCount => Children.Count;

        /// <inheritdoc/>
        public override Priority Priority => Priority.OVERRIDE;

        /// <summary>
        /// Gets the <see cref="List{T}"/> containing all children in the <see cref="EnumerableCollectionNode"/>.
        /// </summary>
        protected List<ExpNode> Children { get; }

        /// <inheritdoc/>
        public override void AddChild(ExpNode node)
        {
            Children.Add(node);
        }

        /// <inheritdoc/>
        public override void InsertChild(BranchNode node)
        {
            ExpNode lastChild = Children[ChildCount - 1];
            Children.RemoveAt(ChildCount - 1);
            node.AddChild(lastChild);
            AddChild(node);
        }

        /// <inheritdoc/>
        public override void ReplaceChild(ExpNode node, int index)
        {
            Children[index] = node;
        }

        /// <inheritdoc/>
        public override ExpNode GetChild(int index)
        {
            return Children[index];
        }

        /// <inheritdoc/>
        public override void ClearChildren()
        {
            Children.Clear();
        }

        /// <inheritdoc/>
        public override bool IsConstant()
        {
            foreach (var child in Children)
            {
                if (!child.IsConstant()) return false;
            }
            return true;
        }

        /// <inheritdoc/>
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
