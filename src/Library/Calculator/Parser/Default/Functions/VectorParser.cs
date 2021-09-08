using Calculator.ExpressionTree;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.Parser.Default.Status;

namespace Calculator.Parser.Default.Functions
{
    public class VectorParser : FunctionParser
    {
        private DefaultParser _childParser;
        private TensorNode _vector;

        public VectorParser()
        {
            _childParser = new DefaultParser();
            _vector = new TensorNode(TensorType.Vector);
        }

        public override ParseError ParseFirstChar(char c)
        {
            if (c == '<')
            {
                return new ParseError();
            }

            return new ParseError(ErrorType.MUST_BE, '<');
        }

        public override ParseError ParseNextChar(char c)
        {
            if ((c == ',' || c == '>') && _depth == 0)
            {
                ParserStatus error = _childParser.Finalize();
                if (error.Failed) return new ParseError(error);

                ExpTree tree = _childParser.Tree;
                _childParser = new DefaultParser();
                if (tree == null)
                {
                    return new ParseError(ErrorType.UNKNOWN);
                }

                _vector.AddChild(tree.Root);

                if (c == '>')
                {
                    _vector.EndDimension((int)TensorType.Vector);
                    Output = _vector;
                }

                return new ParseError();
            }
            else
            {
                if (c == '<')
                {
                    _depth++;
                } else if (c == '>')
                {
                    _depth--;
                }

                ParserStatus result = _childParser.ParseNextChar(c);
                return new ParseError(result);
            }
        }
    }
}
