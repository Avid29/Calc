// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Collections;

namespace Calculator.Operations.Groups.Tensors
{
    /// <summary>
    /// A representation of a matrix using arrays of arrays.
    /// </summary>
    public class MatrixByRow
    {
        private MatrixRow[] _rows;

        /// <summary>
        /// Initializes a new instance of the <see cref="MatrixByRow"/> class.
        /// </summary>
        /// <param name="matrix">The matrix to represent.</param>
        public MatrixByRow(TensorNode matrix)
        {
            Height = matrix.GetDimensionSize(2);
            Width = matrix.GetDimensionSize(1);
            _rows = new MatrixRow[Height];
            for (int i = 0; i < Height; i++) _rows[i] = new MatrixRow(matrix, i);
        }

        /// <summary>
        /// Gets the height of the matrix.
        /// </summary>
        public int Height { get; }

        /// <summary>
        /// Gets the width of the matrix.
        /// </summary>
        public int Width { get; }

        /// <summary>
        /// Gets the <see cref="MatrixRow"/> at <paramref name="index"/>.
        /// </summary>
        /// <param name="index">The row to get.</param>
        /// <returns>The <see cref="MatrixRow"/> at <paramref name="index"/>.</returns>
        public MatrixRow this[int index]
        {
            get => _rows[index];
        }

        /// <summary>
        /// Swaps two rows.
        /// </summary>
        /// <param name="rIndex1">The index of the first row to swap.</param>
        /// <param name="rIndex2">The index of the second row to swap.</param>
        public void SwapRows(int rIndex1, int rIndex2)
        {
            MatrixRow swap = _rows[rIndex1];
            _rows[rIndex1] = _rows[rIndex2];
            _rows[rIndex2] = swap;
        }

        /// <summary>
        /// Converts the <see cref="MatrixByRow"/> back to a <see cref="TensorNode"/>.
        /// </summary>
        /// <returns>The <see cref="MatrixByRow"/> as a <see cref="TensorNode"/>.</returns>
        public TensorNode AsExpNode()
        {
            TensorNode matrix = new TensorNode(Height, Width);
            for (int i = 0; i < Height; i++)
            {
                for (int j = 0; j < Width; j++)
                {
                    matrix.AddChild(_rows[i][j]);
                }
            }

            return matrix;
        }
    }
}
