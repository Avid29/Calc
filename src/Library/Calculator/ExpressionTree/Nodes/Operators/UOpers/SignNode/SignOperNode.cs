// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode
{
    /// <summary>
    /// An <see cref="ExpNode"/> that adjusts the sign of its child.
    /// </summary>
    public class SignOperNode : UOperNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="SignOperNode"/> class.
        /// </summary>
        /// <param name="sign">The <see cref="SignNode.Sign"/>.</param>
        public SignOperNode(Sign sign)
        {
            Sign = sign;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SignOperNode"/> class.
        /// </summary>
        /// <param name="c">The <see cref="SignNode.Sign"/> as a <see cref="char"/>.</param>
        public SignOperNode(char c)
        {
            Sign = c switch
            {
                '+' => Sign.POSITIVE,
                '-' => Sign.NEGATIVE,
                _ => Sign.POSITIVE,
            };
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SignOperNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="SignOperNode"/> to clone.</param>
        public SignOperNode(SignOperNode node)
            : base(node)
        {
            Sign = node.Sign;
        }

        /// <inheritdoc/>
        public override Priority Priority => Priority.SIGN;

        /// <summary>
        /// Gets the <see cref="SignNode.Sign"/> of the <see cref="SignOperNode"/>.
        /// </summary>
        public Sign Sign { get; }

        /// <inheritdoc/>
        public override ExpNode Clone() => new SignOperNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
