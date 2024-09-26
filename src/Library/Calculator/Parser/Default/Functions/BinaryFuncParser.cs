// Adam Dernis 2024

using Calculator.ExpressionTree.Nodes.Operators;
using Calculator.Parser.Default.Status;
using Calculator.Parser.Default.Tokenization;

namespace Calculator.Parser.Default.Functions;

/// <summary>
/// A <see cref="FunctionParser"/> that for parsing <see cref="BOperNode"/>s.
/// </summary>
/// <remarks>
/// Represented as \boper{x1,x2}.
/// </remarks>
public class BinaryFuncParser : FunctionParser
{
    private readonly BOperNode _node;
    private DefaultParser _childParser;
    private State _state;

    /// <summary>
    /// Initializes a new instance of the <see cref="BinaryFuncParser"/> class.
    /// </summary>
    /// <param name="node">The node to create.</param>
    public BinaryFuncParser(BOperNode node)
    {
        _state = State.Opening;
        _node = node;
        _childParser = new DefaultParser(false);
    }

    private enum State
    {
        Opening,
        Expression1Opening,
        Expession1,
        Expression2Opening,
        Expression2,
        Done,
    }

    /// <inheritdoc/>
    public override ParseError ParseNextToken(Token token)
    {
        switch (_state)
        {
            case State.Opening:
                if (token != '{')
                {
                    return new ParseError(ErrorType.MustBe, '{');
                }

                _state = State.Expression1Opening;
                return new ParseError();
            case State.Expression1Opening:
                if (token == ',')
                {
                    return new ParseError(ErrorType.CannotProceed);
                }
                _state = State.Expession1;
                goto case State.Expession1;
            case State.Expession1:
                return ParseExpression1(token);
            case State.Expression2Opening:
                if (token == ',') return new ParseError(ErrorType.CannotProceed);
                _state = State.Expression2;
                goto case State.Expression2;
            case State.Expression2: return ParseExpression2(token);
            default: return new ParseError(ErrorType.Unknown);
        }
    }

    private ParseError ParseExpression1(Token token)
    {
        if (_depth == 0)
        {
            if (token == '}') return new ParseError(ErrorType.InadequateArguments);

            if (token == ',')
            {
                _state = State.Expression2Opening;
                ParseError status = FinalizeChild();
                if (!status.Failed) _childParser = new DefaultParser();
                return status;
            }
        }

        return ParseAsChild(token);
    }

    private ParseError ParseExpression2(Token token)
    {
        if (_depth == 0)
        {
            if (token == ',') return new ParseError(ErrorType.TooManyArguments);

            if (token == '}')
            {
                _state = State.Done;
                ParseError status = FinalizeChild();
                if (!status.Failed) Output = _node;
                return status;
            }
        }

        return ParseAsChild(token);
    }

    private ParseError ParseAsChild(Token token)
    {
        if (token == '{' || token == '<')
        {
            _depth++;
        }
        else if (token == '}' || token == '>')
        {
            _depth--;
        }

        ParserStatus status = _childParser.ParseNextToken(token);
        return new ParseError(status);
    }

    private ParseError FinalizeChild()
    {
        ParserStatus status = _childParser.Finalize();
        if (status.Failed)
        {
            return new ParseError(status);
        }

        _node.AddChild(_childParser.Tree.Root);
        return new ParseError();
    }
}
