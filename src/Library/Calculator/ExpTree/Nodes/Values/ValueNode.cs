namespace Calculator.ExpTree.Nodes.Values
{
    public abstract class ValueNode : ExpNode
    {
        public override Priority Priority => Priority.VALUE;
    }
}
