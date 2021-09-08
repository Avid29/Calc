using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode
{
    public class SignOperNode : UOperNode
    {
        public SignOperNode(SignOperNode node) : base(node)
        {
            Sign = node.Sign;
        }

        public SignOperNode(char c)
        {
            switch (c)
            {
                case '+':
                    Sign = Sign.POSITIVE;
                    break;
                case '-':
                    Sign = Sign.NEGATIVE;
                    break;
                default:
                    Sign = Sign.POSITIVE;
                    break;
            }
        }

        public override Priority Priority => Priority.SIGN;

        public Sign Sign { get; }

        public override ExpNode Clone()
        {
            return new SignOperNode(this);
        }

        public override ExpNode Execute(Operation operation)
        {
            return operation.Execute(this);
        }

        public override string Print(Printer printer)
        {
            return printer.Print(this);
        }
    }
}
