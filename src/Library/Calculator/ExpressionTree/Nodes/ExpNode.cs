using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes
{
    public abstract class ExpNode
    {
        public BranchNode Parent { get; set; }

        public abstract Priority Priority { get; }

        public bool IsRoot => Parent == null;

        public abstract ExpNode Execute(Operation operation);

        public abstract string Print(Printer printer);

        public abstract ExpNode Clone();
    }
}
