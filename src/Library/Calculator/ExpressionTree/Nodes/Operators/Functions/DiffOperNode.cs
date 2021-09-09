// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.Functions
{
    public class DiffOperNode : UOperNode
    {
        public DiffOperNode() { }

        public DiffOperNode(DiffOperNode node)
            : base(node)
        {
            Variable = node.Variable;
        }

        public override Priority Priority => Priority.OVERRIDE;

        public VarValueNode Variable { get; set; }

        public override ExpNode Clone()
        {
            return new DiffOperNode(this);
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
