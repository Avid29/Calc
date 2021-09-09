// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes.Operators.UOpers.SineNode;
using Calculator.Parser.Default.Status;

namespace Calculator.Parser.Default.Functions
{
    /// <summary>
    /// A <see cref="FunctionParser"/> that for parsing a <see cref="SineOperNode"/>.
    /// </summary>
    public class SinusoidalFuncParser : FunctionParser
    {
        private readonly DefaultParser _childParser;

        /// <summary>
        /// Initializes a new instance of the <see cref="SinusoidalFuncParser"/> class.
        /// </summary>
        /// <param name="type">The type of <see cref="ExpressionTree.Nodes.Operators.UOpers.SineNode.SineFunction"/> to create.</param>
        public SinusoidalFuncParser(string type)
        {
            switch (type)
            {
                case "sin": SineFunction = SineFunction.SINE; break;
                case "cos": SineFunction = SineFunction.COSINE; break;
                case "tan": SineFunction = SineFunction.TANGENT; break;
                case "csc": SineFunction = SineFunction.COSECANT; break;
                case "sec": SineFunction = SineFunction.SECANT; break;
                case "cot": SineFunction = SineFunction.COTANGENT; break;
            }

            _childParser = new DefaultParser();
        }

        /// <summary>
        /// Gets the <see cref="ExpressionTree.Nodes.Operators.UOpers.SineNode.SineFunction"/> being created.
        /// </summary>
        public SineFunction SineFunction { get; }

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

                Output = new SineOperNode(SineFunction);
                Output.AddChild(_childParser.Tree.Root);
                return new ParseError();
            }
            else
            {
                if (c == '{')
                {
                    _depth++;
                } else if (c == '}')
                {
                    _depth--;
                }

                ParserStatus status = _childParser.ParseNextChar(c);
                return new ParseError(status);
            }
        }
    }
}
