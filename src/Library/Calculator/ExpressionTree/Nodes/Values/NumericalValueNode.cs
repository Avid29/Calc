// Adam Dernis © 2021

namespace Calculator.ExpressionTree.Nodes.Values
{
    /// <summary>
    /// A base class for <see cref="ValueNode"/>s that have a numerical value.
    /// </summary>
    public abstract class NumericalValueNode : ValueNode
    {
        /// <summary>
        /// Gets the <see cref="NumericalValueNode"/> as a double.
        /// </summary>
        public abstract double DoubleValue { get; }
        
        /// <inheritdoc/>
        public override bool IsConstant() => true;

        /// <inheritdoc/>
        public override bool IsConstantBy(VarValueNode variable) => true;
    }
}
