// Adam Dernis 2024

using Calculator.ExpressionTree;
using Calculator.ExpressionTree.Nodes.Operators.Functions;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Parser.Default.Status;
using Calculator.Parser.Default.Tokenization;

namespace Calculator.Parser.Default.Functions;

/// <summary>
/// A <see cref="FunctionParser"/> for parsing a <see cref="DiffOperNode"/>.
/// </summary>
public class DiffFuncParser : FunctionParser
{
    private readonly DiffOperNode _node;
    private readonly DefaultParser _childParser;
    private State _state;

    /// <summary>
    /// Initializes a new instance of the <see cref="DiffFuncParser"/> class.
    /// </summary>
    public DiffFuncParser()
    {
        _state = State.PreVar;
        _depth = 0;
        _node = new DiffOperNode();
        _childParser = new DefaultParser(false);
    }

    private enum State
    {
        PreVar,
        Var,
        PostVar,
        OpenExpression,
        Expression,
        Done,
    }

    /// <inheritdoc/>
    public override ParseError ParseNextToken(Token token)
    {
        switch (_state)
        {
            case State.PreVar:
                if (token != '[')
                {
                    return new ParseError(ErrorType.MustBe, '[');
                }

                _state = State.Var;
                return new ParseError();

            case State.Var:
                if (token.TokenType != TokenType.Variable)
                {
                    return new ParseError(ErrorType.DerivativeMustBeVariable);
                }

                _node.Variable = new VarValueNode(token);
                _state = State.PostVar;
                return new ParseError();

            case State.PostVar:
                if (token != ']')
                {
                    return new ParseError(ErrorType.MustBe, ']');
                }

                _state = State.OpenExpression;
                return new ParseError();

            case State.OpenExpression:
                if (token != '{')
                {
                    return new ParseError(ErrorType.MustBe, '{');
                }

                _state = State.Expression;
                return new ParseError();

            case State.Expression:
                {
                    if (token == '}' && _depth == 0)
                    {
                        ParserStatus status = _childParser.Finalize();
                        if (status.Failed)
                        {
                            return new ParseError(status);
                        }

                        ExpTree tree = _childParser.Tree;
                        if (tree == null)
                        {
                            return new ParseError(ErrorType.Unknown);
                        }

                        _node.AddChild(tree.Root);
                        _state = State.Done;
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
                        ParserStatus result = _childParser.ParseNextToken(token);
                        return new ParseError(result);
                    }
                }

            default:
                return new ParseError(ErrorType.Unknown);
        }
    }
}
