using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.Printers.Abstract;

namespace Calculator.Printers.Default
{
    public class DefaultPrinter : Printer
    {
        public override string Print(ExpNode node)
        {
            return "";
        }

        public override string Print(PowOperNode node)
        {
            return $"{node.LeftChild.Print(this)} ^ {node.RightChild.Print(this)}";
        }
    }
}
