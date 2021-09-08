using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Collections
{
    public class TensorNode : EnumerableCollectionNode
    {
        private int _dimensionCount;
        private int[] _sizes;

        public TensorNode(TensorType tensorType) : this((int)tensorType) { }

        public TensorNode(int dimensionCount)
        {
            _dimensionCount = dimensionCount;
            _sizes = new int[dimensionCount];
        }

        public TensorNode(TensorNode node) : base(node) { }

        public TensorType TensorType => (TensorType)_dimensionCount;

        public int DimensionCount => _dimensionCount;

        public int GetDimensionSize(int dimension)
        {
            return _sizes[dimension - 1];
        }

        public int EndDimension(int dimension)
        {
            // TODO: Tensors and Matricies
            _sizes[dimension - 1] = Children.Count;
            return _sizes[dimension - 1];
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
