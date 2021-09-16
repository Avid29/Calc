// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.Functions.RowElim
{
    /// <summary>
    /// An <see cref="ExpNode"/> that reduces its child matrix to reduced row-echelon form.
    /// </summary>
    public class RowElimOperNode : UOperNode
    {
        private RowElimMethod _elimMethod;

        /// <summary>
        /// Initializes a new instance of the <see cref="RowElimOperNode"/> class.
        /// </summary>
        /// <param name="rowElim">The method for the row elimination.</param>
        public RowElimOperNode(RowElimMethod rowElim)
        {
            _elimMethod = rowElim;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="RowElimOperNode"/> class.
        /// </summary>
        /// <param name="function">The method for the row elimination.</param>
        public RowElimOperNode(string function)
        {
            switch (function)
            {
                case "ref":
                    _elimMethod = RowElimMethod.Gauss;
                    break;
                case "rref":
                    _elimMethod = RowElimMethod.GaussJordan;
                    break;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="RowElimOperNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="RowElimOperNode"/> to clone.</param>
        public RowElimOperNode(RowElimOperNode node)
            : base(node)
        {
            _elimMethod = node._elimMethod;
        }

        /// <summary>
        /// Gets the Elimination Method.
        /// </summary>
        public RowElimMethod EliminationMethod => _elimMethod;

        /// <inheritdoc/>
        public override Priority Priority => Priority.OVERRIDE;

        /// <inheritdoc/>
        public override ExpNode Clone() => new RowElimOperNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
