// Adam Dernis © 2021

using Calculator.ExpressionTree;
using Calculator.ExpressionTree.Nodes.Operators;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Parser.Default.Functions;
using Calculator.Parser.Default.Status;
using System;

namespace Calculator.Parser.Default
{
    /// <summary>
    /// The default parser for creating <see cref="ExpTree"/>s.
    /// </summary>
    public class DefaultParser
    {
        private ParserState _state;
        private string _input;
        private ExpTree _tree;
        private FunctionParser _activeFunctionParser;
        private string _cache;
        private int _parenthesisDepth;
        private int _position;

        /// <summary>
        /// Initializes a new instance of the <see cref="DefaultParser"/> class.
        /// </summary>
        public DefaultParser()
        {
            _state = ParserState.BEGIN;
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
        public ExpTree Tree => _state == ParserState.DONE ? _tree : null;

        /// <summary>
        /// Parses a complete string and returns the resulting tree and status.
        /// </summary>
        /// <param name="equation">The equation to parse.</param>
        /// <param name="tree">The resulting tree.</param>
        /// <returns>The resulting parsing status.</returns>
        public static ParserStatus Parse(string equation, out ExpTree tree)
        {
            DefaultParser parser = new DefaultParser();
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
            if (_state == ParserState.FUNCTION) return ParseFunction(c);
            if (_state == ParserState.PARTIAL_FUNCTION) return ParsePartialFunction(c);
            if (char.IsDigit(c)) return ParseDigit(c);
            if (char.IsLetter(c)) return ParseLetter(c);

            switch (c)
            {
                // Brackets
                case '[': case '{': case '(': case '<':
                case '>': case ')': case '}': case ']':
                    return ParseBracket(c);

                // Operators
                case '+': case '-':
                case '*': case '/':
                case '^': return ParseOper(c);

                // Other
                case '.': return ParseDecimal();
                case '\\': return ParseEscape();

                // Error by default
                default: return EnterErrorState(ErrorType.CANNOT_PROCEED);
            }
        }

        /// <summary>
        /// Finalizes the tree after all characters are parsed.
        /// </summary>
        /// <returns>The resulting status of finalizing.</returns>
        public ParserStatus Finalize()
        {
            if (_state == ParserState.DONE) return GetSuccessState();
            if (_state == ParserState.ERROR) return EnterErrorState(ErrorType.UNKNOWN);

            CompleteValue();

            if (_parenthesisDepth != 0) return EnterErrorState(ErrorType.UNPAIRED_PARENTHESIS);

            switch (_state)
            {
                // Valid states
                case ParserState.INT:
                case ParserState.FLOAT:
                case ParserState.VARIABLE:
                case ParserState.VALUE:
                    _state = ParserState.DONE;
                    return GetSuccessState();

                // Throw error by default
                default:
                    return EnterErrorState(ErrorType.UNKNOWN);
            }
        }

        private ParserStatus ParseDigit(char c)
        {
            switch (_state)
            {
                case ParserState.VALUE:
                    _tree.AddNode(new MultiplicationOperNode());
                    goto case ParserState.BEGIN;
                case ParserState.BEGIN:
                case ParserState.OPEN_PARENTHESIS:
                case ParserState.UOPER:
                case ParserState.NOPER:
                case ParserState.INT:
                    _state = ParserState.INT;
                    goto case ParserState.FLOAT;
                case ParserState.FLOAT:
                    _cache += c;
                    return GetSuccessState();
                case ParserState.DECIMAL:
                    _state = ParserState.FLOAT;
                    goto case ParserState.FLOAT;
                default:
                    return EnterErrorState(ErrorType.CANNOT_PROCEED);
            }
        }

        private ParserStatus ParseLetter(char c)
        {
            switch (_state)
            {
                case ParserState.BEGIN:
                case ParserState.OPEN_PARENTHESIS:
                case ParserState.UOPER:
                case ParserState.NOPER:
                    _tree.AddNode(new VarValueNode(c));
                    _state = ParserState.VARIABLE;
                    return GetSuccessState();
                case ParserState.INT:
                case ParserState.FLOAT:
                    CompleteValue();
                    goto case ParserState.VARIABLE;
                case ParserState.VALUE:
                case ParserState.VARIABLE:
                    _tree.AddNode(new MultiplicationOperNode());
                    _tree.AddNode(new VarValueNode(c));
                    _state = ParserState.VARIABLE;
                    return GetSuccessState();
                default:
                    return EnterErrorState(ErrorType.CANNOT_PROCEED);
            }
        }

        private ParserStatus ParseOper(char c)
        {
            switch (_state)
            {
                case ParserState.BEGIN:
                case ParserState.OPEN_PARENTHESIS:
                case ParserState.NOPER:
                    return ParseUOper(c);
                case ParserState.INT:
                case ParserState.FLOAT:
                case ParserState.VALUE:
                case ParserState.VARIABLE:
                    CompleteValue();
                    return ParseNOper(c);
                default:
                    return EnterErrorState(ErrorType.CANNOT_PROCEED);
            }
        }

        private ParserStatus ParseNOper(char c)
        {
            if (c == '^') _tree.AddNode(new PowOperNode());
            else _tree.AddNode(NOperNode.MakeNOperNode(c));
            _state = ParserState.NOPER;

            // '-' and '/' as NOPER nodes are parsed as '+' or '*', but need to be followed
            // by the aligning UOPER node.
            if (c == '-' || c == '/')
            {
                _tree.AddNode(UOperNode.MakeUOperNode(c));
                _state = ParserState.UOPER;
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
                    _state = ParserState.UOPER;
                    return GetSuccessState();
                default:
                    return EnterErrorState(ErrorType.CANNOT_PROCEED);
            }
        }

        private ParserStatus ParseBracket(char c)
        {
            switch (_state)
            {
                case ParserState.INT:
                case ParserState.FLOAT:
                    CompleteValue();
                    goto case ParserState.VALUE;
                case ParserState.VALUE:
                case ParserState.VARIABLE:
                    if (c == '(') _tree.AddNode(new MultiplicationOperNode());
                    goto case ParserState.UOPER;
                case ParserState.UOPER:
                case ParserState.NOPER:
                case ParserState.BEGIN:
                case ParserState.OPEN_PARENTHESIS:
                {
                        if (c == '(')
                        {
                            _tree.AddNode(new ParenthesisOperNode());
                            _parenthesisDepth++;
                            _state = ParserState.OPEN_PARENTHESIS;
                        } else if (c == ')')
                        {
                            if (_parenthesisDepth == 0)
                            {
                                return EnterErrorState(ErrorType.UNPAIRED_PARENTHESIS);
                            } else if (_state == ParserState.OPEN_PARENTHESIS)
                            {
                                return EnterErrorState(ErrorType.CANNOT_PROCEED);
                            }

                            _parenthesisDepth--;
                            _tree.CloseParenthesis();
                            _state = ParserState.VALUE;
                        }
                        else if (c == '<')
                        {
                            _activeFunctionParser = FunctionParser.MakeFunctionParser(c);
                            _activeFunctionParser.ParseFirstChar(c);
                            _state = ParserState.FUNCTION;
                        }
                        else
                        {
                            return EnterErrorState(ErrorType.UNPAIRED_PARENTHESIS);
                        }
                        return GetSuccessState();
                }
                default:
                    return EnterErrorState(ErrorType.UNKNOWN);
            }
        }

        private ParserStatus ParseDecimal()
        {
            switch (_state)
            {
                case ParserState.INT:
                    _cache += ".";
                    _state = ParserState.DECIMAL;
                    return GetSuccessState();
                case ParserState.FLOAT:
                    return EnterErrorState(ErrorType.ALREADY_FLOAT);
                case ParserState.BEGIN:
                    return EnterErrorState(ErrorType.CANNOT_BEGIN);
                default:
                    return EnterErrorState(ErrorType.CANNOT_PROCEED);
            }
        }

        private ParserStatus ParseEscape()
        {
            switch (_state)
            {
                case ParserState.INT:
                case ParserState.FLOAT:
                    CompleteValue();
                    goto case ParserState.VALUE;
                case ParserState.VALUE:
                case ParserState.VARIABLE:
                    _tree.AddNode(new MultiplicationOperNode());
                    goto case ParserState.NOPER;
                case ParserState.NOPER:
                case ParserState.UOPER:
                case ParserState.BEGIN:
                case ParserState.OPEN_PARENTHESIS:
                    _cache = string.Empty;
                    _state = ParserState.PARTIAL_FUNCTION;
                    return GetSuccessState();
                case ParserState.PARTIAL_FUNCTION:
                    // TODO: handle new line
                    return EnterErrorState(ErrorType.CANNOT_PROCEED);
                default:
                    return EnterErrorState(ErrorType.CANNOT_PROCEED);
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
                return EnterErrorState(ErrorType.INVALID_FUNCTION);
            }

            _state = ParserState.FUNCTION;
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
                _state = ParserState.VALUE;
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
            _state = ParserState.ERROR;
            return new ParserStatus(errorType, _input, _position, expectedChar);
        }

        private void CompleteValue()
        {
            if (_state != ParserState.INT && _state != ParserState.FLOAT) return;

            double value = Convert.ToDouble(_cache);
            _tree.AddNode(Helpers.MakeNumericalNode(value));
            _cache = string.Empty;
        }
    }
}
