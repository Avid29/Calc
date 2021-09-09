// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Values
{
    /// <summary>
    /// An <see cref="ExpNode"/> representing a double.
    /// </summary>
    public class FloatValueNode : NumericalValueNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="FloatValueNode"/> class.
        /// </summary>
        /// <param name="value">The value of the <see cref="FloatValueNode"/>.</param>
        public FloatValueNode(double value)
        {
            Value = value;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="FloatValueNode"/> class as a <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="FloatValueNode"/> to clone.</param>
        public FloatValueNode(FloatValueNode node)
        {
            Value = node.Value;
        }

        /// <summary>
        /// Gets the value of the <see cref="NumericalValueNode"/> as a double.
        /// </summary>
        public double Value { get; }

        /// <inheritdoc/>
        public override double DoubleValue => Value;

        /// <inheritdoc/>
        public override ExpNode Clone() => new FloatValueNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
