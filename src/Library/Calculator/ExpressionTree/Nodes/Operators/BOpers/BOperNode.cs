// Adam Dernis © 2021

using Calculator.Exceptions.ExpressionTree;
using Calculator.ExpressionTree.Nodes.Values;
using System;

namespace Calculator.ExpressionTree.Nodes.Operators
{
    /// <summary>
    /// A base class for <see cref="OperNode"/>s with two (2) children.
    /// </summary>
    public abstract class BOperNode : OperNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="BOperNode"/> class.
        /// </summary>
        public BOperNode() { }

        /// <summary>
        /// Initializes a new instance of the <see cref="BOperNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="BOperNode"/> to clone.</param>
        protected BOperNode(BOperNode node)
        {
            LeftChild = node.LeftChild.Clone();
            RightChild = node.RightChild.Clone();
        }

        /// <summary>
        /// Gets or sets the left hand child of this <see cref="BOperNode"/>.
        /// </summary>
        public ExpNode LeftChild { get; set; }

        /// <summary>
        /// Gets or sets the right hand child of this <see cref="BOperNode"/>.
        /// </summary>
        public ExpNode RightChild { get; set; }

        /// <inheritdoc/>
        public override int ChildCount
        {
            get
            {
                if (LeftChild == null) return 0;
                else if (RightChild == null) return 1;
                else return 2;
            }
        }

        /// <inheritdoc/>
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

        /// <inheritdoc/>
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

        /// <inheritdoc/>
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

        /// <inheritdoc/>
        public override ExpNode GetChild(int index)
        {
            return index switch
            {
                0 => LeftChild,
                1 => RightChild,
                _ => throw new ArgumentOutOfRangeException($"{nameof(BOperNode)} only contains two (2) children. Zero (0) and one (1) are the only indicies."),
            };
        }

        /// <inheritdoc/>
        public override void ClearChildren()
        {
            LeftChild = null;
            RightChild = null;
        }

        /// <inheritdoc/>
        public override bool IsConstant()
        {
            return LeftChild.IsConstant() && RightChild.IsConstant();
        }

        /// <inheritdoc/>
        public override bool IsConstantBy(VarValueNode variable)
        {
            return LeftChild.IsConstantBy(variable) && RightChild.IsConstantBy(variable);
        }
    }
}
