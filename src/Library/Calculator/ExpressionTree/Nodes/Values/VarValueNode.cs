// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Values
{
    /// <summary>
    /// An <see cref="ExpNode"/> representing a variable value.
    /// </summary>
    public class VarValueNode : ValueNode
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="VarValueNode"/> class.
        /// </summary>
        /// <param name="c">The character representing the variable.</param>
        public VarValueNode(char c)
        {
            Character = c;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="VarValueNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="VarValueNode"/> to clone.</param>
        public VarValueNode(VarValueNode node)
        {
            Character = node.Character;
        }

        /// <summary>
        /// Gets the character representing the variable.
        /// </summary>
        public char Character { get; }

        /// <inheritdoc/>
        public override ExpNode Clone() => new VarValueNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override bool IsConstant() => false;

        /// <inheritdoc/>
        public override bool IsConstantBy(VarValueNode variable) => variable.Character != this.Character;

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
