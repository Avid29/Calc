// Adam Dernis © 2021

using Calculator.Exceptions.ExpressionTree;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpressionTree.Nodes.Values;
using System;

namespace Calculator.ExpressionTree.Nodes.Operators
{
    /// <summary>
    /// A base class for <see cref="OperNode"/>s that have only a single child.
    /// </summary>
    public abstract class UOperNode : OperNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="UOperNode"/> class.
        /// </summary>
        public UOperNode() { }

        /// <summary>
        /// Initializes a new instance of the <see cref="UOperNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="UOperNode"/> to clone.</param>
        protected UOperNode(UOperNode node)
        {
            Child = node.Child;
        }

        /// <summary>
        /// Gets or sets the <see cref="UOperNode"/>'s child.
        /// </summary>
        public ExpNode Child { get; set; }

        /// <inheritdoc/>
        public override int ChildCount => Child == null ? 0 : 1;

        /// <summary>
        /// Makes a new <see cref="UOperNode"/> with the appropiate operator for <see cref="char"/> <paramref name="c"/>.
        /// </summary>
        /// <param name="c">The <see cref="char"/> of the operator to create.</param>
        /// <returns>A new <see cref="UOperNode"/> of the appropiate operator for <see cref="char"/> <paramref name="c"/>.</returns>
        public static UOperNode MakeUOperNode(char c)
        {
            return c switch
            {
                '+' or '-' => new SignOperNode(c),
                '/' => new RecipricalOperNode(),
                _ => null,
            };
        }

        /// <inheritdoc/>
        public override void AddChild(ExpNode node)
        {
            AddChild(node);
        }

        /// <inheritdoc cref="BranchNode.AddChild(ExpNode)"/>
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

        /// <inheritdoc/>
        public override void InsertChild(BranchNode node)
        {
            if (Child != null)
            {
                node.AddChild(Child);
            }

            AddChild(node, true);
        }

        /// <inheritdoc/>
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

        /// <inheritdoc/>
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

        /// <inheritdoc/>
        public override void ClearChildren()
        {
            Child = null;
        }

        /// <inheritdoc/>
        public override bool IsConstant()
        {
            return Child.IsConstant();
        }

        /// <inheritdoc/>
        public override bool IsConstantBy(VarValueNode variable)
        {
            return Child.IsConstantBy(variable);
        }
    }
}
