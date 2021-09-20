// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.Functions.VectorProduct
{
    /// <summary>
    /// An <see cref="ExpNode"/> that finds vector products.
    /// </summary>
    public class VectorProductOperNode : BOperNode
    {
        private VectorProductMethod _productMethod;

        /// <summary>
        /// Initializes a new instance of the <see cref="VectorProductOperNode"/> class.
        /// </summary>
        /// <param name="productMethod">The method for vector multiplication.</param>
        public VectorProductOperNode(VectorProductMethod productMethod)
        {
            _productMethod = productMethod;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="VectorProductOperNode"/> class.
        /// </summary>
        /// <param name="node">The <see cref="VectorProductOperNode"/> to clone.</param>
        public VectorProductOperNode(VectorProductOperNode node)
            : base(node)
        {
            _productMethod = node._productMethod;
        }

        /// <summary>
        /// Gets the product method.
        /// </summary>
        public VectorProductMethod ProductMethod => _productMethod;

        /// <inheritdoc/>
        public override Priority Priority => Priority.MULTIPLICATION;

        /// <inheritdoc/>
        public override ExpNode Clone() => new VectorProductOperNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
