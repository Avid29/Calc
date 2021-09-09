// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.BOpers
{
    /// <summary>
    /// An <see cref="ExpNode"/> that represents a Power operation.
    /// </summary>
    public class PowOperNode : BOperNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="PowOperNode"/> class.
        /// </summary>
        public PowOperNode() { }

        /// <summary>
        /// Initializes a new instance of the <see cref="PowOperNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="PowOperNode"/> to node.</param>
        public PowOperNode(PowOperNode node)
            : base(node) { }

        /// <inheritdoc/>
        public override Priority Priority => Priority.POWER;

        /// <inheritdoc/>
        public override ExpNode Clone() => new PowOperNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
