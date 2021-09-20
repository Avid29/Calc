// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Operators;
using Calculator.Parser.Default.Status;

namespace Calculator.Parser.Default.Functions
{
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
            _state = State.OPENING;
            _node = node;
            _childParser = new DefaultParser();
        }

        private enum State
        {
            OPENING,
            EXPRESSION1_OPENING,
            EXPRESSION1,
            EXPRESSION2_OPENING,
            EXPRESSION2,
            DONE,
        }

        /// <inheritdoc/>
        public override ParseError ParseFirstChar(char c)
        {
            if (c == '{')
            {
                _state = State.EXPRESSION1_OPENING;
                return new ParseError();
            }

            return new ParseError(ErrorType.MUST_BE, '{');
        }

        /// <inheritdoc/>
        public override ParseError ParseNextChar(char c)
        {
            switch (_state)
            {
                case State.EXPRESSION1_OPENING:
                    if (c == ',') return new ParseError(ErrorType.CANNOT_PROCEED);
                    _state = State.EXPRESSION1;
                    goto case State.EXPRESSION1;
                case State.EXPRESSION1: return ParseExpression1(c);
                case State.EXPRESSION2_OPENING:
                    if (c == ',') return new ParseError(ErrorType.CANNOT_PROCEED);
                    _state = State.EXPRESSION2;
                    goto case State.EXPRESSION2;
                case State.EXPRESSION2: return ParseExpression2(c);
                default: return new ParseError(ErrorType.UNKNOWN);
            }
        }

        private ParseError ParseExpression1(char c)
        {
            if (_depth == 0)
            {
                if (c == '}') return new ParseError(ErrorType.INADEQUATE_ARGUMENTS);

                if (c == ',')
                {
                    _state = State.EXPRESSION2_OPENING;
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
                if (c == ',') return new ParseError(ErrorType.TOO_MANY_ARGUMENTS);

                if (c == '}')
                {
                    _state = State.DONE;
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
}
