namespace Calculator.ExpTree.Nodes
{
    public enum Priority
    {
        OVERRIDE = -1,
        VALUE,
        FUNCTION,
        SIGN,
        POWER,
        MULTIPLICATION,
        ADDITION,
    }
}
