// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.UOpers.SineNode
{
    /// <summary>
    /// An <see cref="ExpNode"/> that represents a sine function.
    /// </summary>
    public class SineOperNode : UOperNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="SineOperNode"/> class.
        /// </summary>
        /// <param name="func">The sine function of the <see cref="SineOperNode"/>.</param>
        public SineOperNode(SineFunction func)
        {
            SineFunction = func;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SineOperNode"/> class.
        /// </summary>
        /// <param name="type">The sine function of the <see cref="SineOperNode"/>.</param>
        public SineOperNode(string type)
        {
            switch (type)
            {
                case "sin": SineFunction = SineFunction.SINE; break;
                case "cos": SineFunction = SineFunction.COSINE; break;
                case "tan": SineFunction = SineFunction.TANGENT; break;
                case "csc": SineFunction = SineFunction.COSECANT; break;
                case "sec": SineFunction = SineFunction.SECANT; break;
                case "cot": SineFunction = SineFunction.COTANGENT; break;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SineOperNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="SineOperNode"/> to clone.</param>
        public SineOperNode(SineOperNode node)
            : base(node)
        {
            SineFunction = node.SineFunction;
        }

        /// <summary>
        /// Gets the <see cref="SineNode.SineFunction"/> of the <see cref="SineOperNode"/>.
        /// </summary>
        public SineFunction SineFunction { get; }

        /// <inheritdoc/>
        public override Priority Priority => Priority.OVERRIDE;

        /// <inheritdoc/>
        public override ExpNode Clone() => new SineOperNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
