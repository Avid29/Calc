// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.NOpers
{
    /// <summary>
    /// An <see cref="ExpNode"/> representing an addition operation.
    /// </summary>
    public class AdditionOperNode : NOperNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AdditionOperNode"/> class.
        /// </summary>
        public AdditionOperNode() { }

        /// <summary>
        /// Initializes a new instance of the <see cref="AdditionOperNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="AdditionOperNode"/> to clone.</param>
        public AdditionOperNode(AdditionOperNode node)
            : base(node) { }

        /// <inheritdoc/>
        public override Priority Priority => Priority.ADDITION;

        /// <inheritdoc/>
        public override ExpNode Clone() => new AdditionOperNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
        }
}
