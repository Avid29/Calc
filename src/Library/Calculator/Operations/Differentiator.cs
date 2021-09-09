// Adam Dernis © 2021

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
    /// <summary>
    /// An <see cref="Operation"/> that takes the derivate of <see cref="ExpNode"/>s.
    /// </summary>
    /// <remarks>
    /// Currently only partial derivatives.
    /// </remarks>
    public class Differentiator : Operation
    {
        private readonly VarValueNode _variable;

        /// <summary>
        /// Initializes a new instance of the <see cref="Differentiator"/> class.
        /// </summary>
        /// <param name="variable">The variable to take the derivative over.</param>
        public Differentiator(VarValueNode variable)
        {
            _variable = variable;
        }

        /// <inheritdoc/>
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

        /// <inheritdoc/>
        public override ExpNode Execute(ExpNode node) => node;

        /// <inheritdoc/>
        public override ExpNode Execute(MultiplicationOperNode node)
        {
            // Product rule
            AdditionOperNode aNode = new();
            for (int i = 0; i < node.ChildCount; i++)
            {
                MultiplicationOperNode mNode = new();
                mNode.AddChild(node.GetChild(i).Clone().Execute(this));
                for (int j = 0; j < node.ChildCount; j++)
                {
                    if (j != i) mNode.AddChild(node.GetChild(j).Clone());
                }

                aNode.AddChild(mNode);
            }
            return aNode;
        }

        /// <inheritdoc/>
        public override ExpNode Execute(NumericalValueNode node)
        {
            return Helpers.MakeNumericalNode(0);
        }

        /// <inheritdoc/>
        public override ExpNode Execute(PowOperNode node)
        {
            // TODO: Handle variable in exponent
            if (node.IsConstantBy(_variable)) return Helpers.MakeNumericalNode(0);

            var coefficient = node.RightChild;
            var @base = node.LeftChild;
            var exponent = Helpers.Add(-1, coefficient);
            return Helpers.Multiply(coefficient, Helpers.Pow(@base, exponent));
        }

        /// <inheritdoc/>
        public override ExpNode Execute(ParenthesisOperNode node)
        {
            node.Child = node.Child.Execute(this);
            return node;
        }

        /// <inheritdoc/>
        public override ExpNode Execute(SineOperNode node)
        {
            if (node.IsConstantBy(_variable)) return Helpers.MakeNumericalNode(0);

            // Apply chain rule
            var coefficient = node.Child.Clone().Execute(this);
            // Apply table
            var sinFunc = SineTable(node);
            return Helpers.Multiply(coefficient, sinFunc);
        }

        /// <inheritdoc/>
        public override ExpNode Execute(TensorNode node)
        {
            for (int i = 0; i < node.ChildCount; i++)
            {
                ExpNode diffChild = node.GetChild(i).Execute(this);
                node.ReplaceChild(diffChild, i);
            }

            return node;
        }

        /// <inheritdoc/>
        public override ExpNode Execute(VarValueNode node)
        {
            return Helpers.MakeNumericalNode(node.Character == _variable.Character ? 1 : 0);
        }

        private static ExpNode SineTable(SineOperNode node)
        {
            return node.SineFunction switch
            {
                SineFunction.SINE => new SineOperNode(SineFunction.COSINE) { Child = node.Child },
                SineFunction.COSINE => Helpers.Negative(new SineOperNode(SineFunction.SINE) { Child = node.Child }),
                _ => node,
            };
        }
    }
}