using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SineNode;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Operations.Abstract;

namespace Calculator.Operations
{
    public class Differentiator : Operation
    {
        private VarValueNode _variable;

        public Differentiator(VarValueNode variable)
        {
            _variable = variable;
        }

        public override ExpNode Execute(AdditionOperNode node)
        {
            // Sum rule
            for (int i = 0; i < node.ChildCount; i++)
            {
                ExpNode diffChild = node.GetChild(i).Execute(this);
                node.ReplaceChild(diffChild, i);
            }

            return node;
        }

        public override ExpNode Execute(ExpNode node)
        {
            return node;
        }

        public override ExpNode Execute(MultiplicationOperNode node)
        {
            // Product rule
            AdditionOperNode aNode = new AdditionOperNode();
            for (int i = 0; i < node.ChildCount; i++)
            {
                MultiplicationOperNode mNode = new MultiplicationOperNode();
                mNode.AddChild(node.GetChild(i).Clone().Execute(this));
                for (int j = 0; j < node.ChildCount; j++)
                {
                    if (j != i) mNode.AddChild(node.GetChild(j).Clone());
                }

                aNode.AddChild(mNode);
            }
            return aNode;
        }

        public override ExpNode Execute(NumericalValueNode node)
        {
            return Helpers.MakeNumericalNode(0);
        }

        public override ExpNode Execute(PowOperNode node)
        {
            // TODO: Handle variable in exponent
            if (node.IsConstantBy(_variable)) return Helpers.MakeNumericalNode(0);

            var coefficient = node.RightChild;
            var @base = node.LeftChild;
            var exponent = Helpers.Add(-1, node.RightChild);
            return Helpers.Multiply(coefficient, Helpers.Pow(@base, exponent));
        }

        public override ExpNode Execute(ParenthesisOperNode node)
        {
            node.Child = node.Child.Execute(this);
            return node;
        }

        public override ExpNode Execute(SineOperNode node)
        {
            if (node.IsConstantBy(_variable)) return Helpers.MakeNumericalNode(0);

            // Apply chain rule
            var coefficient = node.Child.Clone().Execute(this);
            // Apply table
            var sinFunc = SineTable(node);
            return Helpers.Multiply(coefficient, sinFunc);
        }

        public override ExpNode Execute(TensorNode node)
        {
            for (int i = 0; i < node.ChildCount; i++)
            {
                ExpNode diffChild = node.GetChild(i).Execute(this);
                node.ReplaceChild(diffChild, i);
            }

            return node;
        }

        public override ExpNode Execute(VarValueNode node)
        {
            return Helpers.MakeNumericalNode(node.Character == _variable.Character ? 1 : 0);
        }

        private ExpNode SineTable(SineOperNode node)
        {
            switch (node.SineFunc)
            {
                case SineFunc.SINE:
                    return new SineOperNode(SineFunc.COSINE) { Child = node.Child };
                case SineFunc.COSINE:
                    return Helpers.Negative(new SineOperNode(SineFunc.SINE) { Child = node.Child });
                default:
                    return node;
            }
        }
    }
}
