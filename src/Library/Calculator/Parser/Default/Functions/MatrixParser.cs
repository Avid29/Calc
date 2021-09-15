// Adam Dernis © 2021

using Calculator.ExpressionTree;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.Parser.Default.Status;
using System;

namespace Calculator.Parser.Default.Functions
{
    /// <summary>
    /// A <see cref="FunctionParser"/> that parses a <see cref="TensorNode"/> for a vector.
    /// </summary>
    /// <remarks>
    /// Vector is represented in form &lt;x1,x2,x3&gt;.
    /// </remarks>
    public class MatrixParser : FunctionParser
    {
        private DefaultParser _childParser;
        private TensorNode _matrix;
        private State _state;
        private string _cache;
        private int[] _sizes;

        /// <summary>
        /// Initializes a new instance of the <see cref="MatrixParser"/> class.
        /// </summary>
        public MatrixParser()
        {
            _childParser = new DefaultParser();
            _state = State.OPEN_X;
            _cache = string.Empty;
            _sizes = new int[2];
        }

        private enum State
        {
            OPEN_X,
            ARGUMENT_X,
            OPEN_Y,
            ARGUMENT_Y,
            OPEN_EXPRESSION,
            EXPRESSION,
            DONE,
        }

        /// <inheritdoc/>
        public override ParseError ParseFirstChar(char c)
        {
            if (c == '[')
            {
                _state = State.ARGUMENT_X;
                return new ParseError();
            }

            return new ParseError(ErrorType.MUST_BE, '[');
        }

        /// <inheritdoc/>
        public override ParseError ParseNextChar(char c)
        {
            switch (_state)
            {
                case State.ARGUMENT_X:
                    return ParseUintArg(c);
                case State.OPEN_Y:
                case State.ARGUMENT_Y:
                    return ParseUintArg(c);
                case State.OPEN_EXPRESSION:
                    if (c == '{')
                    {
                        _state = State.EXPRESSION;
                        _matrix = new TensorNode(_sizes);
                        return new ParseError();
                    }
                    else return new ParseError(ErrorType.CANNOT_PROCEED);
                case State.EXPRESSION:
                    {
                        if ((c == '}' || c == ',') && _depth == 0)
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
                                return new ParseError(ErrorType.UNKNOWN);
                            }

                            _matrix.AddChild(tree.Root);

                            if (c == '}')
                            {
                                _state = State.DONE;
                                Output = _matrix;
                            }

                            return new ParseError();
                        }
                        else
                        {
                            if (c == '{')
                            {
                                _depth++;
                            }
                            else if (c == '}')
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

        private ParseError ParseUintArg(char c)
        {
            if (char.IsDigit(c))
            {
                _cache += c;
                if (_state == State.OPEN_Y) _state = State.ARGUMENT_Y;

                return new ParseError();
            }

            if (c == ',' && _state == State.ARGUMENT_X)
            {
                _state = State.OPEN_Y;
                _sizes[0] = Convert.ToInt32(_cache);
                _cache = string.Empty;
                return new ParseError();
            }
            if (c == ']' && _state == State.ARGUMENT_Y)
            {
                _state = State.OPEN_EXPRESSION;
                _sizes[1] = Convert.ToInt32(_cache);
                _cache = string.Empty;
                return new ParseError();
            }

            return new ParseError(ErrorType.CANNOT_PROCEED);
        }
    }
}
