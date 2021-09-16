﻿// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.Functions;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SineNode;
using Calculator.ExpressionTree.Nodes.Values;
using Calculator.Helpers;
using Calculator.Operations.Abstract;

namespace Calculator.Operations
{
    /// <summary>
    /// An <see cref="Operation"/> that finds the integral of <see cref="ExpNode"/>s.
    /// </summary>
    public class Integrator : Operation
    {
        private readonly VarValueNode _variable;

        /// <summary>
        /// Initializes a new instance of the <see cref="Integrator"/> class.
        /// </summary>
        /// <param name="variable">The variable to find the integral for.</param>
        public Integrator(VarValueNode variable)
        {
            _variable = variable;
        }

        /// <inheritdoc/>
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

        /// <inheritdoc/>
        public override ExpNode Execute(ExpNode node) => node;

        /// <inheritdoc/>
        public override ExpNode Execute(NumericalValueNode node) => ConstantRule(node);

        /// <inheritdoc/>
        public override ExpNode Execute(MultiplicationOperNode node)
        {
            // TODO: Sinusoidal u substitutions
            // TODO: Constants recognitions for v
            Differentiator differentiator = new(_variable);

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

            AdditionOperNode aNode = new();

            // u*vs
            MultiplicationOperNode mNode = new();
            mNode.AddChild(u.Clone());
            for (int i = 0; i < partCount; i++)
            {
                mNode.AddChild(vs[i].Clone());
            }
            aNode.AddChild(mNode);

            // Combinatoric integrals
            for (int i = 0; i < partCount; i++)
            {
                IntegralOperNode intNode = new();
                mNode = new MultiplicationOperNode();
                intNode.Variable = new VarValueNode(_variable);
                mNode.AddChild(u.Clone());
                for (int j = 0; j < partCount; j++)
                {
                    if (i == j) mNode.AddChild(dvs[j].Clone());
                    else mNode.AddChild(vs[j].Clone());
                }
                intNode.AddChild(mNode);
                aNode.AddChild(QuickOpers.Negative(intNode));
            }

            return aNode;
        }

        /// <inheritdoc/>
        public override ExpNode Execute(PowOperNode node)
        {
            // TODO: Handle variable in exponent
            if (node.IsConstantBy(_variable)) return ConstantRule(node);

            // Increment exponent, divide by exponent
            AdditionOperNode exponent = QuickOpers.Add(1, node.RightChild);
            RecipricalOperNode coefficient = QuickOpers.Reciprical(exponent.Clone());
            PowOperNode @base = QuickOpers.Pow(node.LeftChild, exponent);
            return QuickOpers.Multiply(coefficient, @base);
        }

        /// <inheritdoc/>
        public override ExpNode Execute(SignOperNode node)
        {
            node.Child = node.Child.Execute(this);
            return node;
        }

        /// <inheritdoc/>
        public override ExpNode Execute(SineOperNode node)
        {
            if (node.IsConstantBy(_variable)) return ConstantRule(node);

            Differentiator diff = new(_variable);
            // Apply ChainRule
            var coefficient = node.Child.Execute(diff);
            // Apply table
            var sinFunc = SineTable(node);
            return QuickOpers.Multiply(QuickOpers.Reciprical(coefficient), sinFunc);
        }

        /// <inheritdoc/>
        public override ExpNode Execute(VarValueNode node)
        {
            if (node.Character != _variable.Character) return ConstantRule(node);
            return QuickOpers.Multiply(.5, QuickOpers.Pow(node, 2));
        }

        private static ExpNode SineTable(SineOperNode node)
        {
            return node.SineFunction switch
            {
                SineFunction.SINE => QuickOpers.Negative(new SineOperNode(SineFunction.COSINE) { Child = node.Child }),
                SineFunction.COSINE => new SineOperNode(SineFunction.SINE) { Child = node.Child },
                _ => node.Clone(),
            };
        }

        private ExpNode ConstantRule(ExpNode node) => QuickOpers.Multiply(node, _variable.Clone());
    }
}
