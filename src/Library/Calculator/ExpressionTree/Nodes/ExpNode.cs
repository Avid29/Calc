// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes
{
    /// <summary>
    /// A base class for all nodes representing a member of the expression tree.
    /// </summary>
    public abstract class ExpNode
    {
        /// <summary>
        /// Gets or sets the parent node of this <see cref="ExpNode"/>.
        /// </summary>
        public BranchNode Parent { get; set; }

        /// <summary>
        /// Gets the order of operations priority for this <see cref="ExpNode"/>.
        /// </summary>
        public abstract Priority Priority { get; }

        /// <summary>
        /// Gets a value indicating whether or not this is the root node.
        /// </summary>
        public bool IsRoot => Parent == null;

        /// <summary>
        /// Recursively clones this node.
        /// </summary>
        /// <returns>A recrusive clone of this.</returns>
        public abstract ExpNode Clone();

        /// <summary>
        /// Executes an <see cref="Operation"/> on this <see cref="ExpNode"/>.
        /// </summary>
        /// <param name="operation">The <see cref="Operation"/> to execute.</param>
        /// <returns>The resulting <see cref="ExpNode"/> of the <see cref="Operation"/>.</returns>
        public abstract ExpNode Execute(Operation operation);

        /// <summary>
        /// Prints this node using a <see cref="Printer"/>.
        /// </summary>
        /// <param name="printer">The <see cref="Printer"/> to print this node with.</param>
        /// <returns>This node printed by <see cref="Printer"/>.</returns>
        public abstract string Print(Printer printer);

        /// <summary>
        /// Gets if this <see cref="ExpNode"/> or and its children are constant.
        /// </summary>
        /// <remarks>
        /// An <see cref="ExpNode"/> is constant if neither it or any of its children are a <see cref="VarValueNode"/>.
        /// </remarks>
        /// <returns>a value indicating whether or not the <see cref="ExpNode"/> is constant.</returns>
        public abstract bool IsConstant();

        /// <summary>
        /// Gets if this <see cref="ExpNode"/> or and its children are constant with all <see cref="VarValueNode"/> constant except <paramref name="variable"/>.
        /// </summary>
        /// <remarks>
        /// An <see cref="ExpNode"/> is constant by <paramref name="variable"/> if neither it or any of its children are <paramref name="variable"/>.
        /// </remarks>
        /// <param name="variable">The <see cref="VarValueNode"/> that is not constant.</param>
        /// <returns>a value indicating whether or not the <see cref="ExpNode"/> is constant.</returns>
        public abstract bool IsConstantBy(VarValueNode variable);
    }
}
