// Adam Dernis 2024

using Calculator.ExpressionTree;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.Parser.Default.Status;
using Calculator.Parser.Default.Tokenization;
using System;

namespace Calculator.Parser.Default.Functions;

/// <summary>
/// A <see cref="FunctionParser"/> that parses a <see cref="TensorNode"/> for a matrix.
/// </summary>
/// <remarks>
/// Matrix is represented in form \matrix[i,j]{x1,x2,x3,...,x(ij)}.
/// </remarks>
public class MatrixParser : FunctionParser
{
    private DefaultParser _childParser;
    private TensorNode _matrix;
    private State _state;
    private string _cache;
    private readonly int[] _sizes;

    /// <summary>
    /// Initializes a new instance of the <see cref="MatrixParser"/> class.
    /// </summary>
    public MatrixParser()
    {
        _childParser = new DefaultParser();
        _state = State.PreX;
        _cache = string.Empty;
        _sizes = new int[2];
    }

    private enum State
    {
        PreX,
        ArgX,
        XYSeperator,
        ArgY,
        PostY,
        OpenExpression,
        Expression,
        Done,
    }

    /// <inheritdoc/>
    public override ParseError ParseNextToken(Token token)
    {
        switch (_state)
        {
            case State.PreX:
            case State.ArgX:
            case State.XYSeperator:
            case State.ArgY:
            case State.PostY:
                return ParseSizeArgs(token);
            case State.OpenExpression:
                if (token == '{')
                {
                    _state = State.Expression;
                    _matrix = new TensorNode(_sizes);
                    return new ParseError();
                }
                else
                {
                    return new ParseError(ErrorType.CannotProceed);
                }
            case State.Expression:
                {
                    if ((token == '}' || token == ',') && _depth == 0)
                    {
                        ParserStatus status = _childParser.Finalize();
                        if (status.Failed)
                        {
                            return new ParseError(status);
                        }

                        ExpTree tree = _childParser.Tree;
                        _childParser = new DefaultParser();
                        if (tree == null)
                        {
                            return new ParseError(ErrorType.Unknown);
                        }

                        _matrix.AddChild(tree.Root);

                        if (token == '}')
                        {
                            _state = State.Done;
                            Output = _matrix;
                        }

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

    private ParseError ParseSizeArgs(Token token)
    {
        switch (_state)
        {
            case State.PreX:
                if (token == '[')
                {
                    _state = State.ArgX;
                    return new ParseError();
                }

                return new ParseError(ErrorType.MustBe, '[');
            case State.ArgX:
                if (token.TokenType is TokenType.Integer)
                {
                    _sizes[0] = Convert.ToInt32(token.TokenString);
                    _state = State.XYSeperator;
                    return new ParseError();
                }
                break;
            case State.XYSeperator:
                if (token.TokenType is TokenType.Seperator)
                {
                    _state = State.ArgY;
                    return new ParseError();
                }
                break;
            case State.ArgY:
                if (token.TokenType is TokenType.Integer)
                {
                    _sizes[1] = Convert.ToInt32(token.TokenString);
                    _state = State.PostY;
                    return new ParseError();
                }
                break;
            case State.PostY:
                if (token == ']')
                {
                    _state = State.OpenExpression;
                    return new ParseError();
                }
                break;
        }

        return new ParseError(ErrorType.CannotProceed);
    }
}
