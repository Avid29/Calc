using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Values
{
    public class IntValueNode : ValueNode
    {
        public IntValueNode(int value)
        {
            Value = value;
        }

        public int Value { get; }
        
        public override ExpNode Execute(Operation operation)
        {
            return operation.Execute(this);
        }

        public override string Print(Printer printer)
        {
            return printer.Print(this);
        }
    }
}
