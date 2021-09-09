// Adam Dernis © 2021

namespace Calculator.ExpressionTree.Nodes.Values
{
    /// <summary>
    /// An <see cref="ExpNode"/> for nodes that represent a value.
    /// </summary>
    public abstract class ValueNode : ExpNode
    {
        /// <inheritdoc/>
        public override Priority Priority => Priority.VALUE;
    }
}
