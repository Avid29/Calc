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
using System;

namespace Calculator.Parser.Default;

/// <summary>
/// The default parser for creating <see cref="ExpTree"/>s.
/// </summary>
public class DefaultParser
{
    private readonly ExpTree _tree;
    private ParserState _state;
    private string _input;
    private FunctionParser _activeFunctionParser;
    private string _cache;
    private int _parenthesisDepth;
    private int _position;

    /// <summary>
    /// Initializes a new instance of the <see cref="DefaultParser"/> class.
    /// </summary>
    public DefaultParser()
    {
        _state = ParserState.Begin;
        _input = string.Empty;
        _tree = new ExpTree();
        _activeFunctionParser = null;
        _cache = string.Empty;
        _parenthesisDepth = 0;
        _position = 0;
    }

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
        _input = expression;

        // Parse each character one at a time
        foreach (char c in expression)
        {
            ParserStatus status = ParseNextChar(c, true);
            if (status.Failed) return status;
        }

        // Finalize after all characters are parsed.
        Finalize();

        return new ParserStatus(_input, _position);
    }

    /// <summary>
    /// Parses the next <see cref="char"/> in the parsing state-machine.
    /// </summary>
    /// <param name="c">The <see cref="char"/> to parse.</param>
    /// <param name="hasFullString">True if the input is already full, not step by step.</param>
    /// <returns>The resulting parser state.</returns>
    public ParserStatus ParseNextChar(char c, bool hasFullString = false)
    {
        // If input isn't known
        if (!hasFullString) _input += c;
        _position++;

        // Ignore whitespace
        if (char.IsWhiteSpace(c)) return GetSuccessState();

        // All cases return and cannot fall-through
        if (_state == ParserState.Function)
            return ParseFunction(c);
        if (_state == ParserState.PartialFunction)
            return ParsePartialFunction(c);

        if (char.IsDigit(c))
            return ParseDigit(c);

        if (char.IsLetter(c))
            return ParseLetter(c);

        return c switch
        {
            // Brackets
            '[' or '{' or '(' or '<' or '>' or ')' or '}' or ']' => ParseBracket(c),
            // Operators
            '+' or '-' or '*' or '/' or '^' => ParseOper(c),
            // Other
            '.' => ParseDecimal(),
            '\\' => ParseEscape(),
            // Error by default
            _ => EnterErrorState(ErrorType.CannotProceed),
        };
    }

    /// <summary>
    /// Finalizes the tree after all characters are parsed.
    /// </summary>
    /// <returns>The resulting status of finalizing.</returns>
    public ParserStatus Finalize()
    {
        if (_state == ParserState.Done) return GetSuccessState();
        if (_state == ParserState.Error) return EnterErrorState(ErrorType.Unknown);

        CompleteValue();

        if (_parenthesisDepth != 0) return EnterErrorState(ErrorType.UnpairedParenthesis);

        switch (_state)
        {
            // Valid states
            case ParserState.Integer:
            case ParserState.Float:
            case ParserState.Variable:
            case ParserState.Value:
                _state = ParserState.Done;
                return GetSuccessState();

            // Throw error by default
            default:
                return EnterErrorState(ErrorType.Unknown);
        }
    }

    private ParserStatus ParseDigit(char c)
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
            case ParserState.Integer:
                _state = ParserState.Integer;
                goto case ParserState.Float;
            case ParserState.Float:
                _cache += c;
                return GetSuccessState();
            case ParserState.Decimal:
                _state = ParserState.Float;
                goto case ParserState.Float;
            default:
                return EnterErrorState(ErrorType.CannotProceed);
        }
    }

    private ParserStatus ParseLetter(char c)
    {
        switch (_state)
        {
            case ParserState.Begin:
            case ParserState.OpenParenthesis:
            case ParserState.UOper:
            case ParserState.NOper:
                _tree.AddNode(new VarValueNode(c));
                _state = ParserState.Variable;
                return GetSuccessState();
            case ParserState.Integer:
            case ParserState.Float:
                CompleteValue();
                goto case ParserState.Variable;
            case ParserState.Value:
            case ParserState.Variable:
                _tree.AddNode(new MultiplicationOperNode());
                _tree.AddNode(new VarValueNode(c));
                _state = ParserState.Variable;
                return GetSuccessState();
            default:
                return EnterErrorState(ErrorType.CannotProceed);
        }
    }

    private ParserStatus ParseOper(char c)
    {
        switch (_state)
        {
            case ParserState.Begin:
            case ParserState.OpenParenthesis:
            case ParserState.NOper:
                return ParseUOper(c);
            case ParserState.Integer:
            case ParserState.Float:
            case ParserState.Value:
            case ParserState.Variable:
                CompleteValue();
                return ParseNOper(c);
            default:
                return EnterErrorState(ErrorType.CannotProceed);
        }
    }

    private ParserStatus ParseNOper(char c)
    {
        if (c == '^') _tree.AddNode(new PowOperNode());
        else _tree.AddNode(NOperNode.MakeNOperNode(c));
        _state = ParserState.NOper;

        // '-' and '/' as NOPER nodes are parsed as '+' or '*', but need to be followed
        // by the aligning UOPER node.
        if (c == '-' || c == '/')
        {
            _tree.AddNode(UOperNode.MakeUOperNode(c));
            _state = ParserState.UOper;
        }

        return GetSuccessState();
    }

    private ParserStatus ParseUOper(char c)
    {
        switch (c)
        {
            case '+':
            case '-':
                _tree.AddNode(new SignOperNode(c));
                _state = ParserState.UOper;
                return GetSuccessState();
            default:
                return EnterErrorState(ErrorType.CannotProceed);
        }
    }

    private ParserStatus ParseBracket(char c)
    {
        switch (_state)
        {
            case ParserState.Integer:
            case ParserState.Float:
                CompleteValue();
                goto case ParserState.Value;
            case ParserState.Value:
            case ParserState.Variable:
                if (c == '(' || c == '<') _tree.AddNode(new MultiplicationOperNode());
                goto case ParserState.UOper;
            case ParserState.UOper:
            case ParserState.NOper:
            case ParserState.Begin:
            case ParserState.OpenParenthesis:
                {
                    if (c == '(')
                    {
                        _tree.AddNode(new ParenthesisOperNode());
                        _parenthesisDepth++;
                        _state = ParserState.OpenParenthesis;
                    }
                    else if (c == ')')
                    {
                        if (_parenthesisDepth == 0)
                        {
                            return EnterErrorState(ErrorType.UnpairedParenthesis);
                        }
                        else if (_state == ParserState.OpenParenthesis)
                        {
                            return EnterErrorState(ErrorType.CannotProceed);
                        }

                        _parenthesisDepth--;
                        _tree.CloseParenthesis();
                        _state = ParserState.Value;
                    }
                    else if (c == '<')
                    {
                        _activeFunctionParser = FunctionParser.MakeFunctionParser(c);
                        _activeFunctionParser.ParseFirstChar(c);
                        _state = ParserState.Function;
                    }
                    else
                    {
                        return EnterErrorState(ErrorType.UnpairedParenthesis);
                    }
                    return GetSuccessState();
                }
            default:
                return EnterErrorState(ErrorType.Unknown);
        }
    }

    private ParserStatus ParseDecimal()
    {
        switch (_state)
        {
            case ParserState.Integer:
                _cache += ".";
                _state = ParserState.Decimal;
                return GetSuccessState();
            case ParserState.Decimal:
            case ParserState.Float:
                return EnterErrorState(ErrorType.AlreadyFloat);
            case ParserState.Begin:
                return EnterErrorState(ErrorType.CannotBegin);
            default:
                return EnterErrorState(ErrorType.CannotProceed);
        }
    }

    private ParserStatus ParseEscape()
    {
        switch (_state)
        {
            case ParserState.Integer:
            case ParserState.Float:
                CompleteValue();
                goto case ParserState.Value;
            case ParserState.Value:
            case ParserState.Variable:
                _tree.AddNode(new MultiplicationOperNode());
                goto case ParserState.NOper;
            case ParserState.NOper:
            case ParserState.UOper:
            case ParserState.Begin:
            case ParserState.OpenParenthesis:
                _cache = string.Empty;
                _state = ParserState.PartialFunction;
                return GetSuccessState();
            case ParserState.PartialFunction:
                // TODO: handle new line
                return EnterErrorState(ErrorType.CannotProceed);
            default:
                return EnterErrorState(ErrorType.CannotProceed);
        }
    }

    private ParserStatus ParsePartialFunction(char c)
    {
        if (char.IsLetter(c))
        {
            _cache += c;
            return GetSuccessState();
        }

        _activeFunctionParser = FunctionParser.MakeFunctionParser(_cache);
        if (_activeFunctionParser == null)
        {
            return EnterErrorState(ErrorType.InvalidFunction);
        }

        _state = ParserState.Function;
        _cache = string.Empty;
        ParseError parseError = _activeFunctionParser.ParseFirstChar(c);
        return GetSuccessState(parseError);
    }

    private ParserStatus ParseFunction(char c)
    {
        ParseError status = _activeFunctionParser.ParseNextChar(c);
        if (_activeFunctionParser.Output != null)
        {
            _tree.AddNode(_activeFunctionParser.Output);
            _state = ParserState.Value;
        }

        return GetSuccessState(status);
    }

    private ParserStatus GetSuccessState(ParseError error = null)
    {
        if (error != null)
        {
            return new ParserStatus(error, _input, _position);
        }

        return new ParserStatus(_input, _position);
    }

    private ParserStatus EnterErrorState(ErrorType errorType, char expectedChar = '\0')
    {
        _state = ParserState.Error;
        return new ParserStatus(errorType, _input, _position, expectedChar);
    }

    private void CompleteValue()
    {
        if (_state != ParserState.Integer && _state != ParserState.Float) return;

        double value = Convert.ToDouble(_cache);
        _tree.AddNode(QuickOpers.MakeNumericalNode(value));
        _cache = string.Empty;
    }
}
