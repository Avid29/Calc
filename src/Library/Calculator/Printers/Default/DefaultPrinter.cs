using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Printers.Abstract;

namespace Calculator.Printers.Default
{
    public class DefaultPrinter : Printer
    {
        public override string Print(ExpNode node)
        {
            return "";
        }

        public override string Print(FloatValueNode node)
        {
            return $"{node.Value}";
        }

        public override string Print(IntValueNode node)
        {
            return $"{node.Value}";
        }

        public override string Print(PowOperNode node)
        {
            return $"{node.LeftChild.Print(this)}^{node.RightChild.Print(this)}";
        }

        public override string Print(VarValueNode node)
        {
            return $"{node.Character}";
        }
    }
}
