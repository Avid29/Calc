// Adam Dernis © 2021

using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Collections
{
    /// <summary>
    /// An <see cref="ExpNode"/> representing a vector, matrix, or tensor.
    /// </summary>
    public class TensorNode : EnumerableCollectionNode
    {
        private readonly int _dimensionCount;
        private readonly int[] _sizes;

        /// <summary>
        /// Initializes a new instance of the <see cref="TensorNode"/> class.
        /// </summary>
        /// <remarks>
        /// Casts <see cref="Collections.TensorType"/> to an <see cref="int"/> and uses that as dimension count.
        /// </remarks>
        /// <param name="tensorType">The type of <see cref="TensorNode"/> to create.</param>
        public TensorNode(TensorType tensorType)
            : this((int)tensorType) { }

        /// <summary>
        /// Initializes a new instance of the <see cref="TensorNode"/> class.
        /// </summary>
        /// <param name="dimensionCount">The number of dimensions to the tensor.</param>
        public TensorNode(int dimensionCount)
        {
            _dimensionCount = dimensionCount;
            _sizes = new int[dimensionCount];
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="TensorNode"/> class as a clone of <paramref name="node"/>.
        /// </summary>
        /// <param name="node">The <see cref="TensorNode"/> to clone.</param>
        public TensorNode(TensorNode node)
            : base(node) { }

        /// <summary>
        /// Gets a string representing the size of the vector/matrix/tensor.
        /// </summary>
        public string SizeIdentity
        {
            get
            {
                // The size of each dimension seperated by ',' wrapped in "()"
                string cache = "(";
                for (int i = 0; i < _dimensionCount; i++)
                {
                    cache += _sizes[i];
                    if (i != _dimensionCount - 1) cache += ',';
                }
                cache += ")";
                return cache;
            }
        }

        /// <summary>
        /// Gets the type of the <see cref="TensorNode"/>.
        /// </summary>
        public TensorType TensorType => (TensorType)_dimensionCount;

        /// <summary>
        /// Gets the number of dimensions in the <see cref="TensorNode"/>.
        /// </summary>
        public int DimensionCount => _dimensionCount;

        /// <summary>
        /// Gets the size of a dimension in the <see cref="TensorNode"/>.
        /// </summary>
        /// <remarks>
        /// Dimensions are 1 indexed.
        /// </remarks>
        /// <param name="n">The dimension to get the size of.</param>
        /// <returns>The size of the <paramref name="n"/>th dimension.</returns>
        public int GetDimensionSize(int n)
        {
            return _sizes[n - 1];
        }

        /// <summary>
        /// Ends the nth dimension and begins parsing the next dimension for input.
        /// </summary>
        /// <param name="n">The dimension to end.</param>
        /// <returns>The size of <paramref name="n"/>th dimension.</returns>
        public int EndDimension(int n)
        {
            // TODO: Tensors and Matricies
            _sizes[n - 1] = Children.Count;
            return _sizes[n - 1];
        }

        /// <inheritdoc/>
        public override ExpNode Clone() => new TensorNode(this);

        /// <inheritdoc/>
        public override ExpNode Execute(Operation operation) => operation.Execute(this);

        /// <inheritdoc/>
        public override string Print(Printer printer) => printer.Print(this);
    }
}
