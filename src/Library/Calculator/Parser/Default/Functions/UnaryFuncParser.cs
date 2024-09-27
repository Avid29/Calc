// Adam Dernis 2024

using Calculator.ExpressionTree.Nodes.Operators;
using Calculator.Parser.Default.Status;
using Calculator.Parser.Default.Tokenization;

namespace Calculator.Parser.Default.Functions;

/// <summary>
/// A <see cref="FunctionParser"/> that for parsing functions that are <see cref="UOperNode"/>s.
/// </summary>
/// <remarks>
/// Represented as \uoper{x}.
/// </remarks>
public class UnaryFuncParser : FunctionParser
{
    private readonly DefaultParser _childParser;
    private readonly UOperNode _node;
    private bool _begun;

    /// <summary>
    /// Initializes a new instance of the <see cref="UnaryFuncParser"/> class.
    /// </summary>
    /// <param name="node">The node to create.</param>
    public UnaryFuncParser(UOperNode node)
    {
        _node = node;
        _childParser = new DefaultParser(false);
        _begun = false;
    }

    /// <inheritdoc/>
    public override ParseError ParseNextToken(Token token)
    {
        if (!_begun)
        {
            if (token != '{')
            {
                return new ParseError(ErrorType.MustBe, '{');
            }
            
            _begun = true;
            return new ParseError();
        }

        if (token == '}' && _depth == 0)
        {
            ParserStatus status = _childParser.Finalize();
            if (status.Failed)
            {
                return new ParseError(status);
            }

            _node.AddChild(_childParser.Tree.Root);
            Output = _node;
            return new ParseError();
        }
        else
        {
            if (token == '{')
            {
                _depth++;
            }
            else if (token == '}')
            {
                _depth--;
            }

            ParserStatus status = _childParser.ParseNextToken(token);
            return new ParseError(status);
        }
    }
}
