// Adam Dernis © 2021

using Calculator.ExpressionTree;
using Calculator.ExpressionTree.Nodes.Operators.Functions;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Parser.Default.Status;

namespace Calculator.Parser.Default.Functions
{
    public class DiffFuncParser : FunctionParser
    {

        private State _state;
        private DiffOperNode _node;
        private DefaultParser _childParser;

        public DiffFuncParser()
        {
            _state = State.OPEN_VAR;
            _depth = 0;
            _node = new DiffOperNode();
            _childParser = new DefaultParser();
        }

        private enum State
        {
            OPEN_VAR,
            VAR,
            CLOSING_VAR,
            OPEN_EXPRESSION,
            EXPRESSION,
            DONE,
        }

        public override ParseError ParseFirstChar(char c)
        {
            if (c == '[' && _state == State.OPEN_VAR)
            {
                _state = State.VAR;
                return new ParseError();
            }

            return new ParseError(ErrorType.MUST_BE, '[');
        }

        public override ParseError ParseNextChar(char c)
        {
            switch (_state)
            {
                case State.VAR:
                    if (!char.IsLetter(c)) return new ParseError(ErrorType.DERIVATIVE_MUST_BE_VARIABLE);
                    _node.Variable = new VarValueNode(c);
                    _state = State.CLOSING_VAR;
                    return new ParseError();

                case State.CLOSING_VAR:
                    if (c != ']') return new ParseError(ErrorType.MUST_BE, ']');
                    _state = State.OPEN_EXPRESSION;
                    return new ParseError();

                case State.OPEN_EXPRESSION:
                    if (c != '{') return new ParseError(ErrorType.MUST_BE, '{');
                    _state = State.EXPRESSION;
                    return new ParseError();

                case State.EXPRESSION:
                    {
                        if (c == '}' && _depth == 0)
                        {
                            ParserStatus status = _childParser.Finalize();
                            if (status.Failed)
                            {
                                return new ParseError(status);
                            }

                            ExpTree tree = _childParser.Tree;
                            if (tree == null)
                            {
                                return new ParseError(ErrorType.UNKNOWN);
                            }
                            _node.AddChild(tree.Root);
                            _state = State.DONE;
                            Output = _node;
                            return new ParseError();
                        } else
                        {
                            if (c == '{')
                            {
                                _depth++;
                            } else if (c == '}')
                            {
                                _depth--;
                            }
                            ParserStatus result = _childParser.ParseNextChar(c);
                            return new ParseError(result);
                        }
                    }

                default:
                    return new ParseError(ErrorType.UNKNOWN);
            }
        }
    }
}
