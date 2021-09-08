using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Collections
{
    public class TensorNode : EnumerableCollectionNode
    {
        public TensorNode(TensorNode node) : base(node)
        {
        }

        public override ExpNode Clone()
        {
            return new TensorNode(this);
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
