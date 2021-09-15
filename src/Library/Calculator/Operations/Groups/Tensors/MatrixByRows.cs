// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Collections;

namespace Calculator.Operations.Groups.Tensors
{
    public class MatrixByRows
    {
        private MatrixRow[] _rows;

        /// <summary>
        /// Initializes a new instance of the <see cref="MatrixByRows"/> class.
        /// </summary>
        /// <param name="matrix">The matrix to represent.</param>
        public MatrixByRows(TensorNode matrix)
        {
            _rows = new MatrixRow[matrix.GetDimensionSize(1)];
            for (int i = 0; i < _rows.Length; i++) _rows[i] = new MatrixRow(matrix, i);
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
    }
}
