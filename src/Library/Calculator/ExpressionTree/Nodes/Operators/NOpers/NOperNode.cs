// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Values;
using System.Collections.Generic;

namespace Calculator.ExpressionTree.Nodes.Operators
{
    /// <summary>
    /// A base class for <see cref="OperNode"/>s for any number of children.
    /// </summary>
    public abstract class NOperNode : OperNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="NOperNode"/> class.
        /// </summary>
        public NOperNode()
        {
            Children = new List<ExpNode>();
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="NOperNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="NOperNode"/> to clone.</param>
        protected NOperNode(NOperNode node)
        {
            Children = new List<ExpNode>();
            foreach (var child in node.Children)
            {
                Children.Add(child.Clone());
            }
        }

        /// <inheritdoc/>
        public override int ChildCount => Children.Count;
        
        /// <summary>
        /// Gets the list of all child nodes.
        /// </summary>
        protected List<ExpNode> Children { get; }

        /// <summary>
        /// Makes a new <see cref="NOperNode"/> with the appropiate operator for <see cref="char"/> <paramref name="c"/>.
        /// </summary>
        /// <param name="c">The <see cref="char"/> of the operator to create.</param>
        /// <returns>A new <see cref="NOperNode"/> of the appropiate operator for <see cref="char"/> <paramref name="c"/>.</returns>
        public static NOperNode MakeNOperNode(char c)
        {
            return c switch
            {
                '+' or '-' => new AdditionOperNode(),
                '*' or '/' => new MultiplicationOperNode(),
                _ => null,
            };
        }

        /// <inheritdoc/>
        public override void AddChild(ExpNode node)
        {
            Children.Add(node);
            node.Parent = this;
        }

        /// <inheritdoc/>
        public override void ReplaceChild(ExpNode node, int index)
        {
            Children[index] = node;
        }

        /// <inheritdoc/>
        public override void InsertChild(BranchNode node)
        {
            ExpNode lastChild = Children[ChildCount - 1];
            Children.RemoveAt(ChildCount - 1);
            node.AddChild(lastChild);
            AddChild(node);
        }

        /// <summary>
        /// Removes the child at <paramref name="index"/> from the node.
        /// </summary>
        /// <param name="index">The index to remove a child from.</param>
        public void RemoveChild(int index)
        {
            Children.RemoveAt(index);
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

        /// <summary>
        /// Copies children for this node to <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The new parent this nodes children for all children.</param>
        public void TransferChildren(NOperNode node)
        {
            foreach (var child in Children)
            {
                node.AddChild(child);
            }
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
