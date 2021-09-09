using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.UOpers.SineNode
{
    public class SineOperNode : UOperNode
    {
        public SineOperNode(SineOperNode node) : base(node)
        {
            SineFunc = node.SineFunc;
        }

        public SineOperNode(SineFunc func)
        {
            SineFunc = func;
        }

        public SineFunc SineFunc { get; }

        public override Priority Priority => Priority.OVERRIDE;

        public override ExpNode Clone()
        {
            return new SineOperNode(this);
        }

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
