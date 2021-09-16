// Adam Dernis © 2021

namespace Calculator.ExpressionTree.Nodes.Operators.Functions.RowElim
{
    /// <summary>
    /// The method used for row elimination.
    /// </summary>
    public enum RowElimMethod
    {
        /// <summary>
        /// Put the matrix in row-echelon form.
        /// </summary>
        Gauss,

        /// <summary>
        /// Put the matrix in reduced row-echelon form.
        /// </summary>
        GaussJordan,
    }
}
