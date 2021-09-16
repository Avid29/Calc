// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.ExpressionTree.Nodes.Operators;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.Functions;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SineNode;
using Calculator.ExpressionTree.Nodes.Values;

namespace Calculator.Printers.Abstract
{
    /// <summary>
    /// A base class for printers using <see cref="ExpNode.Print(Printer)"/> with visitor pattern.
    /// </summary>
    public abstract class Printer
    {
        // All methods by default call their direct parent type except ExpNode because it is the root type.
        // As a result, types only need to be overriden if they can't be handled by a parent type.

        /// <summary>
        /// Prints an <see cref="AdditionOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="AdditionOperNode"/> to print.</param>
        /// <returns>The <see cref="AdditionOperNode"/> printed to a string.</returns>
        public virtual string Print(AdditionOperNode node) => Print((NOperNode)node);

        /// <summary>
        /// Prints a <see cref="BranchNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="BranchNode"/> to print.</param>
        /// <returns>The <see cref="BranchNode"/> printed to a string.</returns>
        public virtual string Print(BranchNode node) => Print((ExpNode)node);

        /// <summary>
        /// Prints a <see cref="BOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="BOperNode"/> to print.</param>
        /// <returns>The <see cref="BOperNode"/> printed to a string.</returns>
        public virtual string Print(BOperNode node) => Print((OperNode)node);

        /// <summary>
        /// Prints a <see cref="DiffOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="DiffOperNode"/> to print.</param>
        /// <returns>The <see cref="DiffOperNode"/> printed to a string.</returns>
        public virtual string Print(DiffOperNode node) => Print((OperNode)node);

        /// <summary>
        /// Prints a <see cref="EnumerableCollectionNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="EnumerableCollectionNode"/> to print.</param>
        /// <returns>The <see cref="EnumerableCollectionNode"/> printed to a string.</returns>
        public virtual string Print(EnumerableCollectionNode node) => Print((BranchNode)node);

        /// <summary>
        /// Prints an <see cref="ExpNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="ExpNode"/> to print.</param>
        /// <returns>The <see cref="ExpNode"/> printed to a string.</returns>
        public abstract string Print(ExpNode node);

        /// <summary>
        /// Prints a <see cref="FloatValueNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="FloatValueNode"/> to print.</param>
        /// <returns>The <see cref="FloatValueNode"/> printed to a string.</returns>
        public virtual string Print(FloatValueNode node) => Print((ValueNode)node);

        /// <summary>
        /// Prints a <see cref="GaussJordElimOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="GaussJordElimOperNode"/> to print.</param>
        /// <returns>The <see cref="GaussJordElimOperNode"/> printed to a string.</returns>
        public virtual string Print(GaussJordElimOperNode node) => Print((UOperNode)node);

        /// <summary>
        /// Prints an <see cref="IntegralOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="IntegralOperNode"/> to print.</param>
        /// <returns>The <see cref="IntegralOperNode"/> printed to a string.</returns>
        public virtual string Print(IntegralOperNode node) => Print((OperNode)node);

        /// <summary>
        /// Prints an <see cref="IntValueNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="IntValueNode"/> to print.</param>
        /// <returns>The <see cref="IntValueNode"/> printed to a string.</returns>
        public virtual string Print(IntValueNode node) => Print((ValueNode)node);

        /// <summary>
        /// Prints a <see cref="MultiplicationOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="MultiplicationOperNode"/> to print.</param>
        /// <returns>The <see cref="MultiplicationOperNode"/> printed to a string.</returns>
        public virtual string Print(MultiplicationOperNode node) => Print((NOperNode)node);

        /// <summary>
        /// Prints a <see cref="NOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="NOperNode"/> to print.</param>
        /// <returns>The <see cref="NOperNode"/> printed to a string.</returns>
        public virtual string Print(NOperNode node) => Print((OperNode)node);

        /// <summary>
        /// Prints an <see cref="OperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="OperNode"/> to print.</param>
        /// <returns>The <see cref="OperNode"/> printed to a string.</returns>
        public virtual string Print(OperNode node) => Print((BranchNode)node);

        /// <summary>
        /// Prints a <see cref="ParenthesisOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="ParenthesisOperNode"/> to print.</param>
        /// <returns>The <see cref="ParenthesisOperNode"/> printed to a string.</returns>
        public virtual string Print(ParenthesisOperNode node) => Print((UOperNode)node);

        /// <summary>
        /// Prints a <see cref="PowOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="PowOperNode"/> to print.</param>
        /// <returns>The <see cref="PowOperNode"/> printed to a string.</returns>
        public virtual string Print(PowOperNode node) => Print((BOperNode)node);

        /// <summary>
        /// Prints a <see cref="SineOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="SineOperNode"/> to print.</param>
        /// <returns>The <see cref="SineOperNode"/> printed to a string.</returns>
        public virtual string Print(SineOperNode node) => Print((UOperNode)node);

        /// <summary>
        /// Prints a <see cref="SignOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="SignOperNode"/> to print.</param>
        /// <returns>The <see cref="SignOperNode"/> printed to a string.</returns>
        public virtual string Print(SignOperNode node) => Print((UOperNode)node);

        /// <summary>
        /// Prints a <see cref="TensorNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="TensorNode"/> to print.</param>
        /// <returns>The <see cref="TensorNode"/> printed to a string.</returns>
        public virtual string Print(TensorNode node) => Print((EnumerableCollectionNode)node);

        /// <summary>
        /// Prints a <see cref="UOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="UOperNode"/> to print.</param>
        /// <returns>The <see cref="UOperNode"/> printed to a string.</returns>
        public virtual string Print(UOperNode node) => Print((OperNode)node);

        /// <summary>
        /// Prints a <see cref="ValueNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="ValueNode"/> to print.</param>
        /// <returns>The <see cref="ValueNode"/> printed to a string.</returns>
        public virtual string Print(ValueNode node) => Print((ExpNode)node);

        /// <summary>
        /// Prints a <see cref="VarValueNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="VarValueNode"/> to print.</param>
        /// <returns>The <see cref="VarValueNode"/> printed to a string.</returns>
        public virtual string Print(VarValueNode node) => Print((ValueNode)node);
    }
}
