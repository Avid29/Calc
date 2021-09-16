// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;

namespace Calculator.Operations.Groups.Tensors
{
    public class MatrixRow
    {
        private ExpNode[] _values;

        /// <summary>
        /// Initializes a new instance of the <see cref="MatrixRow"/> class.
        /// </summary>
        /// <param name="matrix">The matrix it's a row off.</param>
        /// <param name="row">The row of the matrix represented.</param>
        public MatrixRow(TensorNode matrix, int row)
        {
            int width = matrix.GetDimensionSize(1);
            _values = new ExpNode[width];
            for (int i = 0; i < width; i++)
            {
                _values[i] = matrix.GetChildD(row, i);
            }
        }

        /// <summary>
        /// Gets the item at <paramref name="index"/> in the <see cref="MatrixRow"/>.
        /// </summary>
        /// <param name="index">The index to read from the matrix.</param>
        /// <returns>The item at <paramref name="index"/>.</returns>
        public ExpNode this[int index]
        {
            get => _values[index];
        }

        public void AddRowToRow(MatrixRow row, ExpNode coefficient = null)
        {
            Simplifier simplifier = new Simplifier();
            for (int i = 0; i < _values.Length; i++)
            {
                ExpNode newValue;
                if (coefficient == null) newValue = Helpers.Sum(row[i].Clone(), this[i]);
                else newValue = Helpers.Sum(Helpers.Multiply(row[i].Clone(), coefficient.Clone()), this[i]);
                _values[i] = newValue.Execute(simplifier);
            }
        }

        public void MultiplyRow(ExpNode product)
        {
            Simplifier simplifier = new Simplifier();
            for (int i = 0; i < _values.Length; i++)
            {
                ExpNode newValue = Helpers.Multiply(_values[i], product.Clone());
                _values[i] = newValue.Execute(simplifier);
            }
        }
    }
}
