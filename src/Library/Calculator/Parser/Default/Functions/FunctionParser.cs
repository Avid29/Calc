// Adam Dernis 2024

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators.Functions;
using Calculator.ExpressionTree.Nodes.Operators.Functions.RowElim;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SineNode;
using Calculator.Parser.Default.Status;
using Calculator.Parser.Default.Tokenization;

namespace Calculator.Parser.Default.Functions;

/// <summary>
/// A base class for objects used to parse functions in <see cref="DefaultParser"/>.
/// </summary>
public abstract class FunctionParser
{
    /// <summary>
    /// How many child function parsers there are.
    /// </summary>
    protected int _depth = 0;

    /// <summary>
    /// Gets or sets the output of the <see cref="FunctionParser"/> once finished parsing.
    /// </summary>
    public BranchNode Output { get; protected set; }

    /// <summary>
    /// Makes a <see cref="FunctionParser"/> by function <see cref="char"/>.
    /// </summary>
    /// <param name="c">The function <see cref="char"/>.</param>
    /// <returns>The <see cref="FunctionParser"/> for the <see cref="char"/> <paramref name="c"/>.</returns>
    public static FunctionParser MakeFunctionParser(char c)
    {
        return c switch
        {
            '<' => new VectorParser(),
            _ => null,
        };
    }

    /// <summary>
    /// Makes a <see cref="FunctionParser"/> by function name.
    /// </summary>
    /// <param name="functionName">The function name.</param>
    /// <returns>The <see cref="FunctionParser"/> for the name <paramref name="functionName"/>.</returns>
    public static FunctionParser MakeFunctionParser(string functionName)
    {
        return functionName switch
        {
            "sin" or "cos" or "tan" or
            "csc" or "sec" or "cot" => new UnaryFuncParser(new SineOperNode(functionName)),
            "ref" => new UnaryFuncParser(new RowElimOperNode(RowElimMethod.Gauss)),
            "rref" => new UnaryFuncParser(new RowElimOperNode(RowElimMethod.GaussJordan)),
            "diff" => new DiffFuncParser(),
            "int" => new IntegralFuncParser(),
            "matrix" => new MatrixParser(),
            "proj" => new BinaryFuncParser(new VectorProjOperNode()),
            _ => null,
        };
    }

    /// <summary>
    /// Parses the a character in the function.
    /// </summary>
    /// <param name="c">The character to parse.</param>
    /// <returns>The resulting parser status.</returns>
    public abstract ParseError ParseNextToken(Token token);
}
