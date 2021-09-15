// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.Functions
{
    /// <summary>
    /// An <see cref="ExpNode"/> that reduces its child matrix to reduced row-echelon form.
    /// </summary>
    public class GaussJordElimOperNode : UOperNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="GaussJordElimOperNode"/> class.
        /// </summary>
        public GaussJordElimOperNode()
        { }

        /// <summary>
        /// Initializes a new instance of the <see cref="GaussJordElimOperNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="GaussJordElimOperNode"/> to clone.</param>
        public GaussJordElimOperNode(GaussJordElimOperNode node)
            : base(node) { }

        /// <inheritdoc/>
        public override Priority Priority => Priority.OVERRIDE;

        /// <inheritdoc/>
        public override ExpNode Clone() => new GaussJordElimOperNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
