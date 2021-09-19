// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.Functions
{
    /// <summary>
    /// An <see cref="ExpNode"/> that applies Vector projection on two (2) <see cref="TensorNode"/>.
    /// </summary>
    public class VectorProjOperNode : BOperNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="VectorProjOperNode"/> class.
        /// </summary>
        public VectorProjOperNode()
        { }

        /// <summary>
        /// Initializes a new instance of the <see cref="VectorProjOperNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="VectorProjOperNode"/> to clone.</param>
        public VectorProjOperNode(VectorProjOperNode node)
            : base(node) { }

        /// <inheritdoc/>
        public override Priority Priority => Priority.OVERRIDE;

        /// <inheritdoc/>
        public override ExpNode Clone() => new VectorProjOperNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
