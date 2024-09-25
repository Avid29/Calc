// Adam Dernis 2024

using Calculator.ExpressionTree;
using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.Parser.Default.Status;
using System.Collections.Generic;

namespace Calculator.Parser.Default.Functions;

/// <summary>
/// A <see cref="FunctionParser"/> that parses a <see cref="TensorNode"/> for a vector.
/// </summary>
/// <remarks>
/// Vector is represented in form &lt;x1,x2,x3,...&gt;.
/// </remarks>
public class VectorParser : FunctionParser
{
    private readonly List<ExpNode> _children;
    private DefaultParser _childParser;

    /// <summary>
    /// Initializes a new instance of the <see cref="VectorParser"/> class.
    /// </summary>
    public VectorParser()
    {
        _childParser = new DefaultParser();
        _children = [];
    }

    /// <inheritdoc/>
    public override ParseError ParseFirstChar(char c)
    {
        if (c == '<')
        {
            return new ParseError();
        }

        return new ParseError(ErrorType.MustBe, '<');
    }

    /// <inheritdoc/>
    public override ParseError ParseNextChar(char c)
    {
        if ((c == ',' || c == '>') && _depth == 0)
        {
            ParserStatus error = _childParser.Finalize();
            if (error.Failed) return new ParseError(error);

            ExpTree tree = _childParser.Tree;
            _childParser = new DefaultParser();
            if (tree == null)
            {
                return new ParseError(ErrorType.Unknown);
            }

            _children.Add(tree.Root);
            if (c == '>')
            {
                Output = new TensorNode([_children.Count], _children);
            }

            return new ParseError();
        }
        else
        {
            if (c == '<')
            {
                _depth++;
            }
            else if (c == '>')
            {
                _depth--;
            }

            ParserStatus result = _childParser.ParseNextChar(c);
            return new ParseError(result);
        }
    }
}
