// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.UOpers
{
    /// <summary>
    /// An <see cref="ExpNode"/> that represents a reciprical of its children.
    /// </summary>
    public class RecipricalOperNode : UOperNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="RecipricalOperNode"/> class.
        /// </summary>
        public RecipricalOperNode() { }

        /// <summary>
        /// Initializes a new instance of the <see cref="RecipricalOperNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="RecipricalOperNode"/> to clone.</param>
        public RecipricalOperNode(RecipricalOperNode node)
            : base(node) { }

        /// <inheritdoc/>
        public override Priority Priority => Priority.SIGN;

        /// <inheritdoc/>
        public override ExpNode Clone() => new RecipricalOperNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
