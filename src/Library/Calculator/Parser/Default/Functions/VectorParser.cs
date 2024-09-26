// Adam Dernis 2024

using Calculator.ExpressionTree;
using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.Parser.Default.Status;
using Calculator.Parser.Default.Tokenization;
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
    private bool _begun;

    /// <summary>
    /// Initializes a new instance of the <see cref="VectorParser"/> class.
    /// </summary>
    public VectorParser()
    {
        _childParser = new DefaultParser();
        _children = [];
        _begun = false;
    }

    /// <inheritdoc/>
    public override ParseError ParseNextToken(Token token)
    {
        if (!_begun)
        {
            if (token != '<')
            {
                return new ParseError(ErrorType.MustBe, '<');
            }

            _begun = true;
            return new ParseError();
        }

        if ((token == ',' || token == '>') && _depth == 0)
        {
            ParserStatus error = _childParser.Finalize();
            if (error.Failed)
            {
                return new ParseError(error);
            }

            ExpTree tree = _childParser.Tree;
            _childParser = new DefaultParser();
            if (tree == null)
            {
                return new ParseError(ErrorType.Unknown);
            }

            _children.Add(tree.Root);
            if (token == '>')
            {
                Output = new TensorNode([_children.Count], _children);
            }

            return new ParseError();
        }
        else
        {
            if (token == '<')
            {
                _depth++;
            }
            else if (token == '>')
            {
                _depth--;
            }

            ParserStatus result = _childParser.ParseNextToken(token);
            return new ParseError(result);
        }
    }
}
