// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;

namespace Calculator.Operations.Groups.Tensors
{
    public class MatrixRow
    {
        private ExpNode[] _values;

        public MatrixRow(TensorNode matrix, int row)
        {
            int width = matrix.GetDimensionSize(1);
            _values = new ExpNode[width];
            for (int i = 0; i < width; i++)
            {
                _values[i] = matrix.GetChild(row, i);
            }
        }
    }
}
