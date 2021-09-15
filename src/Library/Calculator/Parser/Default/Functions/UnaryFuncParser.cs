// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Operators;
using Calculator.Parser.Default.Status;

namespace Calculator.Parser.Default.Functions
{
    /// <summary>
    /// A <see cref="FunctionParser"/> that for parsing functions that are <see cref="UOperNode"/>s.
    /// </summary>
    public class UnaryFuncParser : FunctionParser
    {
        private readonly DefaultParser _childParser;
        private readonly UOperNode _node;

        /// <summary>
        /// Initializes a new instance of the <see cref="UnaryFuncParser"/> class.
        /// </summary>
        /// <param name="node">The node to create.</param>
        public UnaryFuncParser(UOperNode node)
        {
            _node = node;
            _childParser = new DefaultParser();
        }

        /// <inheritdoc/>
        public override ParseError ParseFirstChar(char c)
        {
            if (c != '{')
            {
                return new ParseError(ErrorType.MUST_BE, '{');
            }
            return new ParseError();
        }

        /// <inheritdoc/>
        public override ParseError ParseNextChar(char c)
        {
            if (c == '}' && _depth == 0)
            {
                ParserStatus status = _childParser.Finalize();
                if (status.Failed)
                {
                    return new ParseError(status);
                }

                _node.AddChild(_childParser.Tree.Root);
                Output = _node;
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

                ParserStatus status = _childParser.ParseNextChar(c);
                return new ParseError(status);
            }
        }
    }
}
