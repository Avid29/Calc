// Adam Dernis 2024

using Calculator.Parser.Default.Status;
using Microsoft.Toolkit.Diagnostics;
using System;
using System.Collections.Generic;
using System.Net.NetworkInformation;

namespace Calculator.Parser.Default.Tokenization;

public class Tokenizer
{
    private readonly List<Token> _tokens;
    private TokenizerState _state;
    private string _cache;
    private TokenType? _cacheTokenType;

    /// <summary>
    /// Initializes a new instance of the <see cref="Tokenizer"/> class.
    /// </summary>
    public Tokenizer()
    {
        _tokens = [];
        _state = TokenizerState.Begin;
        _cache = string.Empty;
        _cacheTokenType = null;
        Input = string.Empty;
        Position = 0;
    }

    /// <summary>
    /// Gets the list of tokens evaluated by the tokenizer.
    /// </summary>
    public IReadOnlyList<Token> Tokens => _state is not TokenizerState.Error ? _tokens : null;

    /// <summary>
    /// Gets the input string being handled.
    /// </summary>
    public string Input { get; private set; }

    /// <summary>
    /// Gets the position within the input string of the tokenizer.
    /// </summary>
    public int Position { get; private set; }

    /// <summary>
    /// An event evoked when a new token is created.
    /// </summary>
    public event EventHandler<Token> TokenCreatedEvent;

    public ParserStatus ParseString(string expression)
    {
        Input = expression;

        foreach (char c in expression)
        {
            var status = ParseNextChar(c);
            if (status.Failed)
                return status;
        }

        return GetSuccessState();
    }
    
    /// <summary>
    /// Parses the next <see cref="char"/> in the tokenizing state-machine.
    /// </summary>
    /// <param name="c">The <see cref="char"/> to parse.</param>
    /// <param name="hasFullString">True if the input is already full, not step by step.</param>
    /// <returns>The resulting parser state.</returns>
    public ParserStatus ParseNextChar(char c, bool hasFullString = false)
    {
        // If input isn't provided, track each character as provided
        if (!hasFullString)
            Input += c;

        Position++;

        return ParseCharacter(c);
    }

    private ParserStatus ParseCharacter(char c)
    {
        return _state switch
        {
            TokenizerState.Begin => ParseFromBegin(c),
            TokenizerState.Integer => ParseFromInteger(c),
            TokenizerState.Float => ParseFromFloat(c),
            TokenizerState.Function => ParseFromFunction(c),
            TokenizerState.Done => throw new InvalidOperationException(),
            TokenizerState.Error => throw new InvalidOperationException(),
            _ => throw new NotImplementedException(),
        };
    }

    private ParserStatus ParseFromBegin(char c)
    {
        // Ignore whitespace between tokens
        if (char.IsWhiteSpace(c))
            return GetSuccessState();

        if (char.IsDigit(c))
        {
            return HandleCharacter(c, TokenType.Integer, TokenizerState.Integer);
        }

        if (char.IsLetter(c))
        {
            return HandleCharacter(c, TokenType.Variable);
        }

        return c switch
        {
            '[' or '{' or '(' or '<' or
            '>' or ')' or '}' or ']' => HandleCharacter(c, TokenType.Bracket),
            '+' or '-' or '*' or '/' or '^' => HandleCharacter(c, TokenType.Operator),
            '.' => HandleCharacter(c, newState:TokenizerState.Float),
            ',' => HandleCharacter(c, TokenType.Seperator),
            '\\' => HandleCharacter(c, newState:TokenizerState.Function),
            _ => EnterErrorState(ErrorType.CannotProceed),
        };
    }

    private ParserStatus ParseFromInteger(char c)
    {
        if (char.IsDigit(c))
        {
            return HandleCharacter(c, TokenType.Integer, TokenizerState.Integer);
        }

        if (c is '.')
        {
            return HandleCharacter(c, newState: TokenizerState.Float);
        }

        return CompleteAndContinue(c);
    }

    private ParserStatus ParseFromFloat(char c)
    {
        if (char.IsDigit(c))
        {
            return HandleCharacter(c, TokenType.Float, TokenizerState.Float);
        }

        if (c == '.')
        {

        }

        return CompleteAndContinue(c);
    }

    private ParserStatus ParseFromFunction(char c)
    {
        if (char.IsLetter(c))
        {
            return HandleCharacter(c, TokenType.FunctionName, TokenizerState.Function);
        }

        return CompleteAndContinue(c);
    }

    private ParserStatus CompleteAndContinue(char c)
    {
        var status = CompleteCacheToken();
        if (status.Failed)
            return status;

        return ParseCharacter(c);
    }

    private ParserStatus CompleteCacheToken()
    {
        if (_cacheTokenType is null)
            return EnterErrorState(ErrorType.CannotProceed);

        Token token = new(_cache, _cacheTokenType.Value, Position);
        _tokens.Add(token);
        TokenCreatedEvent?.Invoke(this, token);
        
        // Reset cache
        _cache = string.Empty;
        _cacheTokenType = null;
        _state = TokenizerState.Begin;
        return GetSuccessState();
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="c">The character being processed.</param>
    /// <param name="newToken">The token created by handling the character, if any.</param>
    /// <param name="newState">The state to leave the tokenizer after this character.</param>
    /// <param name="type">The type of token being formed.</param>
    private ParserStatus HandleCharacter(char c, TokenType? type = null, TokenizerState newState = TokenizerState.Begin)
    {
        _cache += c;
        _cacheTokenType = type;

        if (newState is TokenizerState.Begin)
        {
            if (type is null)
                ThrowHelper.ThrowArgumentException(nameof(type));

            return CompleteCacheToken();
        }

        _state = newState;
        return GetSuccessState();
    }
    
    private ParserStatus GetSuccessState() => new(Input, Position);

    private ParserStatus GetErrorState(ParseError error) => new(error, Input, Position);

    private ParserStatus EnterErrorState(ErrorType errorType, char expectedChar = '\0')
    {
        _state = TokenizerState.Error;
        return new ParserStatus(errorType, Input, Position, expectedChar);
    }
}
