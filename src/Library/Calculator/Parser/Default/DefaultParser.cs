using Calculator.ExpressionTree;
using Calculator.ExpressionTree.Nodes;
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
    public class DefaultParser
    {
        private State _state;
        private string _input;
        private ExpTree _tree;
        private FunctionParser _activeFunctionParser;
        private string _cache;
        private int _parenthesisDepth;
        private int _position;

        public DefaultParser()
        {
            _state = State.BEGIN;
            _input = "";
            _tree = new ExpTree();
            _activeFunctionParser = null;
            _cache = "";
            _parenthesisDepth = 0;
            _position = 0;
        }

        public ExpTree Tree => _state == State.DONE ? _tree : null;

        public ParserStatus ParseString(string expression)
        {
            _input = expression;

            foreach (char c in expression)
            {
                ParserStatus status = ParseNextChar(c, true);
                if (status.Failed)
                {
                    return status;
                }
            }

            Finalize();

            return new ParserStatus(_input, _position);
        }

        public ParserStatus ParseNextChar(char c, bool hasFullString = false)
        {
            if (!hasFullString)
            {
                _input += c;
            }
            _position++;

            if (char.IsWhiteSpace(c))
            {
                return GetSuccessState();
            }
            
            if (_state == State.FUNCTION)
            {
                return ParseFunction(c);
            }
            else if (_state == State.PARTIAL_FUNCTION)
            {
                return ParsePartialFunction(c);
            }
            else if (char.IsDigit(c))
            {
                return ParseDigit(c);
            }
            else if (char.IsLetter(c))
            {
                return ParseLetter(c);
            }
            else
            {
                switch (c)
                {
                    case '[':
                    case '{':
                    case '(':
                    case '<':
                    case '>':
                    case ')':
                    case '}':
                    case ']':
                        return ParseBracket(c);
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                    case '^':
                        return ParseOper(c);
                    case '.':
                        return ParseDecimal();
                    case '\\':
                        return ParseEscape();
                    default:
                        return EnterErrorState(ErrorType.CANNOT_PROCEED);
                }
            }
        }

        public ParserStatus Finalize()
        {
            if (_state == State.DONE) return GetSuccessState();
            if (_state == State.ERROR) return EnterErrorState(ErrorType.UNKNOWN);

            CompleteValue();

            if (_parenthesisDepth != 0) return EnterErrorState(ErrorType.UNPAIRED_PARENTHESIS);

            switch (_state)
            {
                case State.INT:
                case State.FLOAT:
                case State.VARIABLE:
                case State.VALUE:
                    _state = State.DONE;
                    return GetSuccessState();

                default:
                    return EnterErrorState(ErrorType.UNKNOWN);
            }
        }

        private ParserStatus ParseDigit(char c)
        {
            switch (_state)
            {
                case State.VALUE:
                    _tree.AddNode(new MultiplicationOperNode());
                    goto case State.BEGIN;
                case State.BEGIN:
                case State.OPEN_PARENTHESIS:
                case State.UOPER:
                case State.NOPER:
                case State.INT:
                    _state = State.INT;
                    goto case State.FLOAT;
                case State.FLOAT:
                    _cache += c;
                    return GetSuccessState();
                case State.DECIMAL:
                    _state = State.FLOAT;
                    goto case State.FLOAT;
                default:
                    return EnterErrorState(ErrorType.CANNOT_PROCEED);
            }
        }

        private ParserStatus ParseLetter(char c)
        {
            switch (_state)
            {
                case State.BEGIN:
                case State.OPEN_PARENTHESIS:
                case State.UOPER:
                case State.NOPER:
                    _tree.AddNode(new VarValueNode(c));
                    _state = State.VARIABLE;
                    return GetSuccessState();
                case State.INT:
                case State.FLOAT:
                    CompleteValue();
                    goto case State.VARIABLE;
                case State.VALUE:
                case State.VARIABLE:
                    _tree.AddNode(new MultiplicationOperNode());
                    _tree.AddNode(new VarValueNode(c));
                    _state = State.VARIABLE;
                    return GetSuccessState();
                default:
                    return EnterErrorState(ErrorType.CANNOT_PROCEED);
            }
        }

        private ParserStatus ParseOper(char c)
        {
            switch (_state)
            {
                case State.BEGIN:
                case State.OPEN_PARENTHESIS:
                case State.NOPER:
                    return ParseUOper(c);
                case State.INT:
                case State.FLOAT:
                case State.VALUE:
                case State.VARIABLE:
                    CompleteValue();
                    return ParseNOper(c);
                default:
                    return EnterErrorState(ErrorType.CANNOT_PROCEED);
            }
        }

        private ParserStatus ParseNOper(char c)
        {
            if (c == '^')
            {
                _tree.AddNode(new PowOperNode());
            }
            else
            {
                _tree.AddNode(NOperNode.MakeNOperNode(c));
            }
            _state = State.NOPER;

            if (c == '-' || c == '/')
            {
                _tree.AddNode(UOperNode.MakeUOperNode(c));
                _state = State.UOPER;
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
                    _state = State.UOPER;
                    return GetSuccessState();
                default:
                    return EnterErrorState(ErrorType.CANNOT_PROCEED);
            }
        }

        private ParserStatus ParseBracket(char c)
        {
            switch (_state)
            {
                case State.INT:
                case State.FLOAT:
                    CompleteValue();
                    goto case State.UOPER;
                case State.VALUE:
                case State.VARIABLE:
                    _tree.AddNode(new MultiplicationOperNode());
                    goto case State.UOPER;
                case State.UOPER:
                case State.NOPER:
                case State.BEGIN:
                case State.OPEN_PARENTHESIS:
                {
                        if (c == '(')
                        {
                            _tree.AddNode(new ParenthesisOperNode());
                            _parenthesisDepth++;
                            _state = State.OPEN_PARENTHESIS;
                        } else if (c == ')')
                        {
                            if (_parenthesisDepth == 0)
                            {
                                return EnterErrorState(ErrorType.UNPAIRED_PARENTHESIS);
                            } else if (_state == State.OPEN_PARENTHESIS)
                            {
                                return EnterErrorState(ErrorType.CANNOT_PROCEED);
                            }

                            _parenthesisDepth--;
                            _tree.CloseParenthesis();
                            _state = State.VALUE;
                        } else
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
                case State.INT:
                    _cache += ".";
                    _state = State.DECIMAL;
                    return GetSuccessState();
                case State.FLOAT:
                    return EnterErrorState(ErrorType.ALREADY_FLOAT);
                case State.BEGIN:
                    return EnterErrorState(ErrorType.CANNOT_BEGIN);
                default:
                    return EnterErrorState(ErrorType.CANNOT_PROCEED);
            }
        }

        private ParserStatus ParseEscape()
        {
            switch (_state)
            {
                case State.INT:
                case State.FLOAT:
                    CompleteValue();
                    goto case State.VALUE;
                case State.VALUE:
                case State.VARIABLE:
                    _tree.AddNode(new MultiplicationOperNode());
                    goto case State.NOPER;
                case State.NOPER:
                case State.UOPER:
                case State.BEGIN:
                case State.OPEN_PARENTHESIS:
                    _cache = "";
                    _state = State.PARTIAL_FUNCTION;
                    return GetSuccessState();
                case State.PARTIAL_FUNCTION:
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

            _state = State.FUNCTION;
            _cache = "";
            ParseError parseError = _activeFunctionParser.ParseFirstChar(c);
            return GetSuccessState(parseError);
        }

        private ParserStatus ParseFunction(char c)
        {
            ParseError status = _activeFunctionParser.ParseNextChar(c);
            if (_activeFunctionParser.Output != null)
            {
                _tree.AddNode(_activeFunctionParser.Output);
                _state = State.VALUE;
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
            _state = State.ERROR;
            return new ParserStatus(errorType, _input, _position, expectedChar);
        }

        private void CompleteValue()
        {
            if (_state != State.INT && _state != State.FLOAT) return;

            double value = Convert.ToDouble(_cache);
            _tree.AddNode(Helpers.MakeValueNode(value));
            _cache = "";
        }
    }
}
