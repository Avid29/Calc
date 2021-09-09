// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.NOpers
{
    /// <summary>
    /// An <see cref="ExpNode"/> representing a multiplication operation.
    /// </summary>
    public class MultiplicationOperNode : NOperNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="MultiplicationOperNode"/> class.
        /// </summary>
        public MultiplicationOperNode() { }

        /// <summary>
        /// Initializes a new instance of the <see cref="MultiplicationOperNode"/> class as clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="MultiplicationOperNode"/> to clone.</param>
        public MultiplicationOperNode(NOperNode node)
            : base(node) { }

        /// <inheritdoc/>
        public override Priority Priority => Priority.MULTIPLICATION;

        /// <inheritdoc/>
        public override ExpNode Clone() => new MultiplicationOperNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
