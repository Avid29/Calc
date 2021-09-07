using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpTree.Nodes
{
    public abstract class ExpNode
    {
        public BranchNode Parent { get; set; }

        public abstract Priority Priority { get; }

        public abstract ExpNode Execute(Operation operation);

        public abstract string Print(Printer printer);

        public bool IsRoot()
        {
            return Parent == null;
        }
    }
}
