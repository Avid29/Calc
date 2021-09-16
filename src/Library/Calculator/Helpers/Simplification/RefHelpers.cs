// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Operations.Groups.Tensors;

namespace Calculator.Helpers.Simplification
{
    /// <summary>
    /// A class containing methods for helping with GuassJordan elimination.
    /// </summary>
    public static class RefHelpers
    {
        /// <summary>
        /// Gets the leading (first non-zero) column in each row of the matrix.
        /// </summary>
        /// <param name="matrix">The <see cref="MatrixByRow"/> to determine leading columns for.</param>
        /// <returns>An array containing the leading columns of each row.</returns>
        public static int[] GetLeadingColumns(MatrixByRow matrix)
        {
            int[] leadingPositions = new int[matrix.Height];
            for (int i = 0; i < matrix.Height; i++)
            {
                int pos = GetLeadingColumn(matrix[i]);
                leadingPositions[i] = pos;
            }

            return leadingPositions;
        }

        /// <summary>
        /// Gets the leading (first non-zero) column in a <see cref="MatrixRow"/>.
        /// </summary>
        /// <param name="row">The <see cref="MatrixRow"/> to check.</param>
        /// <returns>The leading column of the <see cref="MatrixRow"/>.</returns>
        public static int GetLeadingColumn(MatrixRow row)
        {
            int col = 0;
            while (col < row.Width && !(row[col] is NumericalValueNode node && node.DoubleValue != 0)) col++;
            return col;
        }

        /// <summary>
        /// Gets the row containing the lowest value in an array of integers.
        /// </summary>
        /// <param name="leadingPositions">The array of integers.</param>
        /// <param name="startRow">The offset to begin searching on.</param>
        /// <returns>The row of the lowest value.</returns>
        public static int GetLeftMostColumn(int[] leadingPositions, int startRow = 0)
        {
            int lowestValue = int.MaxValue;
            int lowestValueRow = 0;

            for (int i = startRow; i < leadingPositions.Length; i++)
            {
                if (leadingPositions[i] < lowestValue)
                {
                    lowestValue = leadingPositions[i];
                    lowestValueRow = i;
                }
            }

            return lowestValueRow;
        }
    }
}
