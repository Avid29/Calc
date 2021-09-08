using Calculator.ExpressionTree.Nodes.Operators.UOpers.SineNode;
using Calculator.Parser.Default.Status;

namespace Calculator.Parser.Default.Functions
{
    public class SinusoidalFuncParser : FunctionParser
    {
        private DefaultParser _childParser;

        public SineFunc SineFunc { get; }

        public SinusoidalFuncParser(string type)
        {
            switch (type)
            {
                case "sin": SineFunc = SineFunc.SINE; break;
                case "cos": SineFunc = SineFunc.COSINE; break;
                case "tan": SineFunc = SineFunc.TANGENT; break;
                case "csc": SineFunc = SineFunc.COSECANT; break;
                case "sec": SineFunc = SineFunc.SECANT; break;
                case "cot": SineFunc = SineFunc.COTANGENT; break;
            }
        }

        public override ParseError ParseFirstChar(char c)
        {
            if (c != '{')
            {
                return new ParseError(ErrorType.MUST_BE, '{');
            }
            return new ParseError();
        }

        public override ParseError ParseNextChar(char c)
        {
            if (c == '}' && _depth == 0)
            {
                ParserStatus status = _childParser.Finalize();
                if (status.Failed)
                {
                    return new ParseError(status);
                }

                Output = new SineOperNode(SineFunc);
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
