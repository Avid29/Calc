// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.Functions
{
    /// <summary>
    /// A <see cref="ExpNode"/> that represents a derivative operation.
    /// </summary>
    /// <remarks>
    /// Currently only partial derivatives.
    /// </remarks>
    public class DiffOperNode : UOperNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="DiffOperNode"/> class.
        /// </summary>
        public DiffOperNode() { }

        /// <summary>
        /// Initializes a new instance of the <see cref="DiffOperNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="DiffOperNode"/> to clone.</param>
        public DiffOperNode(DiffOperNode node)
            : base(node)
        {
            Variable = node.Variable;
        }

        /// <inheritdoc/>
        public override Priority Priority => Priority.OVERRIDE;

        /// <summary>
        /// Gets or sets the <see cref="VarValueNode"/> to differentiate for.
        /// </summary>
        public VarValueNode Variable { get; set; }

        /// <inheritdoc/>
        public override ExpNode Clone() => new DiffOperNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
