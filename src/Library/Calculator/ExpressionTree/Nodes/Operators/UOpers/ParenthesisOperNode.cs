// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.UOpers
{
    /// <summary>
    /// An <see cref="ExpNode"/> that represents parenthesis.
    /// </summary>
    public class ParenthesisOperNode : UOperNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="ParenthesisOperNode"/> class.
        /// </summary>
        public ParenthesisOperNode()
        {
            IsClosed = false;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="ParenthesisOperNode"/> class as clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="ParenthesisOperNode"/> to clone.</param>
        public ParenthesisOperNode(ParenthesisOperNode node)
            : base(node)
        {
            IsClosed = node.IsClosed;
        }

        /// <inheritdoc/>
        /// <remarks>
        /// Changes value after closing.
        /// </remarks>
        public override Priority Priority => IsClosed ? Priority.VALUE : Priority.OVERRIDE;

        /// <summary>
        /// Gets or sets a value indicating whether or not the <see cref="ParenthesisOperNode"/> has been closed in parsing.
        /// </summary>
        public bool IsClosed { get; set; }

        /// <inheritdoc/>
        public override ExpNode Clone() => new ParenthesisOperNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
