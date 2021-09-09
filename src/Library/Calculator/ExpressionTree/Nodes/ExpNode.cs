// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes
{
    public abstract class ExpNode
    {
        public BranchNode Parent { get; set; }

        public abstract Priority Priority { get; }

        public bool IsRoot => Parent == null;

        public abstract ExpNode Clone();

        public abstract ExpNode Execute(Operation operation);

        public abstract string Print(Printer printer);

        public abstract bool IsConstant();

        public abstract bool IsConstantBy(VarValueNode variable);
    }
}
