using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.UOpers.SineNode
{
    public class SineOperNode : UOperNode
    {
        public SineOperNode(SineFunc func)
        {
            SineFunc = func;
        }

        public SineFunc SineFunc { get; }

        public override Priority Priority => Priority.OVERRIDE;

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
