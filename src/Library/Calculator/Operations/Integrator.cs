using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.Functions;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SineNode;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Operations.Abstract;
using Calculator.Printers.Default;

namespace Calculator.Operations
{
    public class Integrator : Operation
    {
        private VarValueNode _variable;

        public Integrator(VarValueNode variable)
        {
            _variable = variable;
        }

        public override ExpNode Execute(AdditionOperNode node)
        {
            // Sum rule
            for (int i = 0; i < node.ChildCount; i++)
            {
                ExpNode simpleChild = node.GetChild(i).Execute(this);
                node.ReplaceChild(simpleChild, i);
            }

            return node;
        }

        public override ExpNode Execute(ExpNode node)
        {
            return node;
        }

        public override ExpNode Execute(NumericalValueNode node)
        {
            return ConstantRule(node);
        }

        public override ExpNode Execute(MultiplicationOperNode node)
        {
            Differentiator differentiator = new Differentiator(_variable);

            // \int{u'vwx} = uvwx - \int{uv'wx} - \int{uvw'x} - \int{uvwx'}
            int partCount = node.ChildCount - 1;

            // Get u and du
            ExpNode du = node.GetChild(partCount);
            ExpNode u = du.Clone().Execute(this);

            // Get dvs and vs
            ExpNode[] dvs = new ExpNode[partCount];
            ExpNode[] vs = new ExpNode[partCount];
            for (int i = 0; i < partCount; i++)
            {
                vs[i] = node.GetChild(i);
                dvs[i] = vs[i].Clone().Execute(differentiator);
            }

            AdditionOperNode aNode = new AdditionOperNode();

            // u*vs
            MultiplicationOperNode mNode = new MultiplicationOperNode();
            mNode.AddChild(u.Clone());
            for (int i = 0; i < partCount; i++)
            {
                mNode.AddChild(vs[i].Clone());
            }
            aNode.AddChild(mNode);

            // Combinatoric integrals
            for (int i = 0; i < partCount; i++)
            {
                IntegralOperNode intNode = new IntegralOperNode();
                mNode = new MultiplicationOperNode();
                intNode.Variable = new VarValueNode(_variable);
                mNode.AddChild(u.Clone());
                for (int j = 0; j < partCount; j++)
                {
                    if (i == j) mNode.AddChild(dvs[j].Clone());
                    else mNode.AddChild(vs[j].Clone());
                }
                intNode.AddChild(mNode);
                aNode.AddChild(Helpers.Negative(intNode));
            }

            return aNode;
        }

        public override ExpNode Execute(PowOperNode node)
        {
            // TODO: IsConstant by

            // Increment exponent, divide by exponent
            AdditionOperNode exponent = Helpers.Add(1, node.RightChild);
            RecipricalOperNode coefficient = Helpers.Reciprical(exponent.Clone());
            PowOperNode @base = Helpers.Pow(node.LeftChild, exponent);
            return Helpers.Multiply(coefficient, @base);
        }

        public override ExpNode Execute(SignOperNode node)
        {
            node.Child = node.Child.Execute(this);
            return node;
        }

        public override ExpNode Execute(SineOperNode node)
        {
            Differentiator diff = new Differentiator(_variable);
            // Apply ChainRule
            var coefficient = node.Child.Execute(diff);
            // Apply table
            var sinFunc = SineTable(node);
            return Helpers.Multiply(Helpers.Reciprical(coefficient), sinFunc);
        }

        public override ExpNode Execute(VarValueNode node)
        {
            // TODO: ConstantBy
            return Helpers.Multiply(.5, Helpers.Pow(node, 2));
        }

        private ExpNode ConstantRule(ExpNode node)
        {
            return Helpers.Multiply(node, _variable.Clone());
        }

        private ExpNode SineTable(SineOperNode node)
        {
            switch (node.SineFunc)
            {
                case SineFunc.SINE:
                    return Helpers.Negative(new SineOperNode(SineFunc.COSINE) { Child = node.Child });
                case SineFunc.COSINE:
                    return new SineOperNode(SineFunc.SINE) { Child = node.Child };
                default:
                    return node.Clone();
            }
        }
    }
}
