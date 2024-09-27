// Adam Dernis 2024

using Calculator.ExpressionTree;
using Calculator.ExpressionTree.Nodes.Operators;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Helpers;
using Calculator.Parser.Default.Functions;
using Calculator.Parser.Default.Status;
using Calculator.Parser.Default.Tokenization;
using System;

namespace Calculator.Parser.Default;

/// <summary>
/// The default parser for creating <see cref="ExpTree"/>s.
/// </summary>
public class DefaultParser
{
    private Tokenizer? _tokenizer;
    private readonly ExpTree _tree;
    private ParserState _state;
    private FunctionParser _activeFunctionParser;
    private int _parenthesisDepth;

    /// <summary>
    /// Initializes a new instance of the <see cref="DefaultParser"/> class.
    /// </summary>
    public DefaultParser(bool tokenize = true)
    {
        if (tokenize)
        {
            _tokenizer = new();
            _tokenizer.TokenCreatedEvent += OnTokenizerTokenCreatedEvent;
        }

        _state = ParserState.Begin;
        _tree = new ExpTree();
        _activeFunctionParser = null;
        _parenthesisDepth = 0;
    }

    private void OnTokenizerTokenCreatedEvent(object sender, Token e) => ParseNextToken(e);

    /// <summary>
    /// Gets the created tree if done.
    /// </summary>
    public ExpTree Tree => _state == ParserState.Done ? _tree : null;

    /// <summary>
    /// Parses a complete string and returns the resulting tree and status.
    /// </summary>
    /// <param name="equation">The equation to parse.</param>
    /// <param name="tree">The resulting tree.</param>
    /// <returns>The resulting parsing status.</returns>
    public static ParserStatus Parse(string equation, out ExpTree tree)
    {
        DefaultParser parser = new();
        ParserStatus result = parser.ParseString(equation);

        // Errors are automatically handled like this
        tree = parser.Tree;
        return result;
    }

    /// <summary>
    /// Parses a complete string and returns the resulting status.
    /// </summary>
    /// <param name="expression">The expression to parse.</param>
    /// <returns>The resulting parsing status.</returns>
    public ParserStatus ParseString(string expression)
    {
        // Parse each character one at a time
        foreach (char c in expression)
        {
            ParserStatus status = ParseNextChar(c);
            if (status.Failed) return status;
        }

        // Finalize after all characters are parsed.
        Finalize();

        return new ParserStatus(_tokenizer.Input, _tokenizer.Position);
    }

    /// <summary>
    /// Parses the next <see cref="char"/> in the parsing state-machine.
    /// </summary>
    /// <param name="c">The <see cref="char"/> to parse.</param>
    /// <returns>The resulting parser state.</returns>
    public ParserStatus ParseNextChar(char c)
    {
        // TODO: Specify error type
        if (_tokenizer is null)
            return EnterErrorState(ErrorType.Unknown);

        return _tokenizer.ParseNextChar(c);
    }

    public ParserStatus ParseNextToken(Token token)
    {
        if (_state is ParserState.Function)
            return ParseInFunction(token);

        return token.TokenType switch
        {
            TokenType.Operator => ParseOperator(token),
            TokenType.Integer or
            TokenType.Float => ParseNumber(token),
            TokenType.Variable => ParseVariable(token),
            TokenType.FunctionName => ParseFunction(token),
            TokenType.Bracket => ParseBracket(token),
            _ => EnterErrorState(ErrorType.Unknown), // TODO: Specify error type
        };
    }

    /// <summary>
    /// Finalizes the tree after all characters are parsed.
    /// </summary>
    /// <returns>The resulting status of finalizing.</returns>
    public ParserStatus Finalize()
    {
        if (_tokenizer is not null)
        {
            var status = ParseNextChar(' ');
            _tokenizer.TokenCreatedEvent -= OnTokenizerTokenCreatedEvent;
        }

        if (_parenthesisDepth != 0)
            return EnterErrorState(ErrorType.UnpairedParenthesis);

        switch (_state)
        {
            // Valid states
            case ParserState.Variable:
            case ParserState.Value:
                _state = ParserState.Done;
                return GetSuccessState();

            // Throw error by default
            default:
                return EnterErrorState(ErrorType.Unknown);
        }
    }

    private ParserStatus ParseNumber(Token token)
    {
        switch (_state)
        {
            case ParserState.Value:
                _tree.AddNode(new MultiplicationOperNode());
                goto case ParserState.Begin;
            case ParserState.Begin:
            case ParserState.OpenParenthesis:
            case ParserState.UOper:
            case ParserState.NOper:
                double value = Convert.ToDouble(token.TokenString);
                _tree.AddNode(QuickOpers.MakeNumericalNode(value));
                _state = ParserState.Value;
                return GetSuccessState(token);
            default:
                return EnterErrorState(ErrorType.CannotProceed, token);
        }
    }

    private ParserStatus ParseVariable(Token token)
    {
        char c = token.TokenString[0];

        switch (_state)
        {
            case ParserState.Value:
            case ParserState.Variable:
                _tree.AddNode(new MultiplicationOperNode());
                goto case ParserState.Begin;
            case ParserState.Begin:
            case ParserState.OpenParenthesis:
            case ParserState.UOper:
            case ParserState.NOper:
                _tree.AddNode(new VarValueNode(c));
                _state = ParserState.Value;
                return GetSuccessState(token);
            default:
                return EnterErrorState(ErrorType.CannotProceed, token);
        }
    }

    private ParserStatus ParseOperator(Token token)
    {
        switch (_state)
        {
            case ParserState.Begin:
            case ParserState.OpenParenthesis:
            case ParserState.NOper:
                return ParseUOperator(token);
            case ParserState.Value:
                return ParseNOperator(token);
            default:
                return EnterErrorState(ErrorType.CannotProceed, token);
        }

        ParserStatus ParseUOperator(Token token)
        {
            char c = token.TokenString[0];
            if (c is '+' or '-')
            {
                _tree.AddNode(new SignOperNode(c));
                _state = ParserState.UOper;
                return GetSuccessState(token);
            }

            return EnterErrorState(ErrorType.CannotProceed, token);
        }

        ParserStatus ParseNOperator(Token token)
        {
            char c = token.TokenString[0];
            if (c is '^')
            {
                _tree.AddNode(new PowOperNode());
            }
            else
            {
                _tree.AddNode(NOperNode.MakeNOperNode(c));
            }

            _state = ParserState.NOper;

            // TODO: Move this to the MakeNOperNode method.
            // '-' and '/' as NOPER nodes are parsed as '+' or '*', but need to be followed
            // by the aligning UOPER node.
            if (c == '-' || c == '/')
            {
                _tree.AddNode(UOperNode.MakeUOperNode(c));
                _state = ParserState.UOper;
            }

            return GetSuccessState(token);
        }
    }

    private ParserStatus ParseFunction(Token token)
    {
        _activeFunctionParser = FunctionParser.MakeFunctionParser(token.TokenString.TrimStart('\\'));
        if (_activeFunctionParser is null)
        {
            return EnterErrorState(ErrorType.InvalidFunction, token);
        }

        _state = ParserState.Function;
        return GetSuccessState(token);
    }

    private ParserStatus ParseBracket(Token token)
    {
        char c = token.TokenString[0];

        switch (_state)
        {
            case ParserState.Value:
            case ParserState.Variable:
                if (c is'(' or '<')
                {
                    _tree.AddNode(new MultiplicationOperNode());
                }
                goto case ParserState.Begin;
            case ParserState.Begin:
            case ParserState.OpenParenthesis:
            case ParserState.UOper:
            case ParserState.NOper:
                {
                    switch (c)
                    {
                        case '(':
                            _tree.AddNode(new ParenthesisOperNode());
                            _parenthesisDepth++;
                            _state = ParserState.OpenParenthesis;
                            return GetSuccessState(token);
                        case ')':
                            if (_parenthesisDepth <= 0)
                            {
                                return EnterErrorState(ErrorType.UnpairedParenthesis, token);
                            }

                            if (_state is ParserState.OpenParenthesis)
                            {
                                return EnterErrorState(ErrorType.CannotProceed, token);
                            }

                            _parenthesisDepth--;
                            _tree.CloseParenthesis();
                            _state = ParserState.Value;
                            return GetSuccessState(token);
                        case '<':
                            _activeFunctionParser = FunctionParser.MakeFunctionParser(c);
                            _activeFunctionParser.ParseNextToken(token);
                            _state = ParserState.Function;
                            return GetSuccessState(token);
                        default:
                            return EnterErrorState(ErrorType.UnpairedParenthesis, token);
                    }
                }
            default:
                return EnterErrorState(ErrorType.Unknown, token);
        }
    }

    private ParserStatus ParseInFunction(Token token)
    {
        ParseError error = _activeFunctionParser.ParseNextToken(token);
        if (_activeFunctionParser.Output is not null)
        {
            _tree.AddNode(_activeFunctionParser.Output);
            _state = ParserState.Value;
        }

        return GetStatus(token, error);
    }

    private ParserStatus GetStatus(Token token, ParseError? error) => error is null ? GetSuccessState(token) : GetErrorState(token, error);

    private ParserStatus GetSuccessState(Token token = null) => new(_tokenizer?.Input ?? string.Empty, token?.Position ?? _tokenizer?.Position ?? 0);

    private ParserStatus GetErrorState(Token token, ParseError error) => new(error, _tokenizer?.Input ?? string.Empty, token.Position);

    private ParserStatus EnterErrorState(ErrorType errorType, Token? token = null, char expectedChar = '\0')
    {
        _state = ParserState.Error;
        return new ParserStatus(errorType, _tokenizer?.Input ?? string.Empty, token?.Position ?? _tokenizer?.Position ?? 0, expectedChar);
    }
}
