// Adam Dernis © 2021

namespace Calculator.ExpressionTree.Nodes
{
    public enum Priority
    {
        OVERRIDE = -1,
        VALUE,
        SIGN,
        POWER,
        MULTIPLICATION,
        ADDITION,
    }
}
