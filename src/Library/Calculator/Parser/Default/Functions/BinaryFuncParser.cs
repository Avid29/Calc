// Adam Dernis 2024

using Calculator.ExpressionTree.Nodes.Operators;
using Calculator.Parser.Default.Status;

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
        _childParser = new DefaultParser();
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
    public override ParseError ParseFirstChar(char c)
    {
        if (c == '{')
        {
            _state = State.Expression1Opening;
            return new ParseError();
        }

        return new ParseError(ErrorType.MustBe, '{');
    }

    /// <inheritdoc/>
    public override ParseError ParseNextChar(char c)
    {
        switch (_state)
        {
            case State.Expression1Opening:
                if (c == ',') return new ParseError(ErrorType.CannotProceed);
                _state = State.Expession1;
                goto case State.Expession1;
            case State.Expession1: return ParseExpression1(c);
            case State.Expression2Opening:
                if (c == ',') return new ParseError(ErrorType.CannotProceed);
                _state = State.Expression2;
                goto case State.Expression2;
            case State.Expression2: return ParseExpression2(c);
            default: return new ParseError(ErrorType.Unknown);
        }
    }

    private ParseError ParseExpression1(char c)
    {
        if (_depth == 0)
        {
            if (c == '}') return new ParseError(ErrorType.InadequateArguments);

            if (c == ',')
            {
                _state = State.Expression2Opening;
                ParseError status = FinalizeChild();
                if (!status.Failed) _childParser = new DefaultParser();
                return status;
            }
        }

        return ParseAsChild(c);
    }

    private ParseError ParseExpression2(char c)
    {
        if (_depth == 0)
        {
            if (c == ',') return new ParseError(ErrorType.TooManyArguments);

            if (c == '}')
            {
                _state = State.Done;
                ParseError status = FinalizeChild();
                if (!status.Failed) Output = _node;
                return status;
            }
        }

        return ParseAsChild(c);
    }

    private ParseError ParseAsChild(char c)
    {
        if (c == '{' || c == '<')
        {
            _depth++;
        }
        else if (c == '}' || c == '>')
        {
            _depth--;
        }

        ParserStatus status = _childParser.ParseNextChar(c);
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
