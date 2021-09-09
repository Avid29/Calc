// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.Functions
{
    /// <summary>
    /// A <see cref="ExpNode"/> that represents an integral operation.
    /// </summary>
    public class IntegralOperNode : UOperNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="IntegralOperNode"/> class.
        /// </summary>
        public IntegralOperNode() { }

        /// <summary>
        /// Initializes a new instance of the <see cref="IntegralOperNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="IntegralOperNode"/> to clone.</param>
        public IntegralOperNode(IntegralOperNode node)
            : base(node)
        {
            IsDeterminate = node.IsDeterminate;
            Variable = node.Variable;
            UpperBound = node.UpperBound;
            LowerBound = node.LowerBound;
        }

        /// <inheritdoc/>
        public override Priority Priority => Priority.OVERRIDE;

        // TODO: Remove is determinate field and check by upper and lower bound state.
        /// <summary>
        /// Gets or sets a value indicating whether or not this <see cref="IntegralOperNode"/> is determinate.
        /// </summary>
        public bool IsDeterminate { get; set; }

        /// <summary>
        /// Gets or sets the <see cref="VarValueNode"/> to integrate for.
        /// </summary>
        public VarValueNode Variable { get; set; }

        /// <summary>
        /// Gets or sets the upper bounds of the integral.
        /// </summary>
        public ExpNode UpperBound { get; set; }

        /// <summary>
        /// Gets or sets the lower bounds of the integral.
        /// </summary>
        public ExpNode LowerBound { get; set; }

        /// <inheritdoc/>
        public override ExpNode Clone() => new IntegralOperNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
