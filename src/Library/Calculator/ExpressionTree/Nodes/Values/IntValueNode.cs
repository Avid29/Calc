// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Values
{
    /// <summary>
    /// An <see cref="ExpNode"/> representing an integer.
    /// </summary>
    public class IntValueNode : NumericalValueNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="IntValueNode"/> class.
        /// </summary>
        /// <param name="value">The value of the <see cref="IntValueNode"/>.</param>
        public IntValueNode(int value)
        {
            Value = value;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="IntValueNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="IntValueNode"/> to clone.</param>
        public IntValueNode(IntValueNode node)
        {
            Value = node.Value;
        }

        /// <summary>
        /// Gets the value of the <see cref="NumericalValueNode"/> as an int.
        /// </summary>
        public int Value { get; }

        /// <inheritdoc/>
        public override double DoubleValue => Value;

        /// <inheritdoc/>
        public override ExpNode Clone() => new IntValueNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
