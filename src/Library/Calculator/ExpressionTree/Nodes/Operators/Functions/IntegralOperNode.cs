using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.Functions
{
    public class IntegralOperNode : UOperNode
    {
        public IntegralOperNode() { }

        public IntegralOperNode(IntegralOperNode node) : base(node)
        {
            IsDeterminate = node.IsDeterminate;
            Variable = node.Variable;
            UpperBound = node.UpperBound;
            LowerBound = node.LowerBound;
        }

        public override Priority Priority => Priority.OVERRIDE;

        public bool IsDeterminate { get; set; }

        public VarValueNode Variable { get; set; }

        public ExpNode UpperBound { get; set; }

        public ExpNode LowerBound { get; set; }

        public override ExpNode Clone()
        {
            return new IntegralOperNode(this);
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
