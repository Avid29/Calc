// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Collections;
using Calculator.ExpressionTree.Nodes.Operators;
using Calculator.ExpressionTree.Nodes.Operators.BOpers;
using Calculator.ExpressionTree.Nodes.Operators.Functions;
using Calculator.ExpressionTree.Nodes.Operators.Functions.RowElim;
using Calculator.ExpressionTree.Nodes.Operators.Functions.VectorProduct;
using Calculator.ExpressionTree.Nodes.Operators.NOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SineNode;
using Calculator.ExpressionTree.Nodes.Values;

namespace Calculator.Operations.Abstract
{
    /// <summary>
    /// The base class for operations using <see cref="ExpNode.Execute(Operation)"/> with visitor pattern.
    /// </summary>
    public abstract class Operation
    {
        // All methods by default call their direct parent type except ExpNode because it is the root type.
        // As a result, types only need to be overriden if they can't be handled by a parent type.

        /// <summary>
        /// Executes operation on an <see cref="AdditionOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="AdditionOperNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on an <see cref="AdditionOperNode"/>.</returns>
        public virtual ExpNode Execute(AdditionOperNode node) => Execute((NOperNode)node);

        /// <summary>
        /// Executes operation on a <see cref="BranchNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="BranchNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="BranchNode"/>.</returns>
        public virtual ExpNode Execute(BranchNode node) => Execute((ExpNode)node);

        /// <summary>
        /// Executes operation on a <see cref="BOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="BOperNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="BOperNode"/>.</returns>
        public virtual ExpNode Execute(BOperNode node) => Execute((OperNode)node);

        /// <summary>
        /// Executes operation on a <see cref="DiffOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="DiffOperNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="DiffOperNode"/>.</returns>
        public virtual ExpNode Execute(DiffOperNode node) => Execute((OperNode)node);

        /// <summary>
        /// Executes operation on an <see cref="EnumerableCollectionNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="EnumerableCollectionNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on an <see cref="EnumerableCollectionNode"/>.</returns>
        public virtual ExpNode Execute(EnumerableCollectionNode node) => Execute((BranchNode)node);

        /// <summary>
        /// Executes operation on an <see cref="ExpNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="ExpNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on an <see cref="ExpNode"/>.</returns>
        public abstract ExpNode Execute(ExpNode node);

        /// <summary>
        /// Executes operation on a <see cref="FloatValueNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="FloatValueNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="FloatValueNode"/>.</returns>
        public virtual ExpNode Execute(FloatValueNode node) => Execute((NumericalValueNode)node);

        /// <summary>
        /// Executes operation on a <see cref="RowElimOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="RowElimOperNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="RowElimOperNode"/>.</returns>
        public virtual ExpNode Execute(RowElimOperNode node) => Execute((UOperNode)node);

        /// <summary>
        /// Executes operation on an <see cref="IntegralOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="IntegralOperNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on an <see cref="IntegralOperNode"/>.</returns>
        public virtual ExpNode Execute(IntegralOperNode node) => Execute((OperNode)node);

        /// <summary>
        /// Executes operation on an <see cref="IntValueNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="IntValueNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on an <see cref="IntValueNode"/>.</returns>
        public virtual ExpNode Execute(IntValueNode node) => Execute((NumericalValueNode)node);

        /// <summary>
        /// Executes operation on a <see cref="MultiplicationOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="MultiplicationOperNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="MultiplicationOperNode"/>.</returns>
        public virtual ExpNode Execute(MultiplicationOperNode node) => Execute((NOperNode)node);

        /// <summary>
        /// Executes operation on a <see cref="NOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="NOperNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="NOperNode"/>.</returns>
        public virtual ExpNode Execute(NOperNode node) => Execute((OperNode)node);

        /// <summary>
        /// Executes operation on a <see cref="NumericalValueNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="NumericalValueNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="NumericalValueNode"/>.</returns>
        public virtual ExpNode Execute(NumericalValueNode node) => Execute((ValueNode)node);

        /// <summary>
        /// Executes operation on an <see cref="OperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="OperNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on an <see cref="OperNode"/>.</returns>
        public virtual ExpNode Execute(OperNode node) => Execute((BranchNode)node);

        /// <summary>
        /// Executes operation on a <see cref="ParenthesisOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="ParenthesisOperNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="ParenthesisOperNode"/>.</returns>
        public virtual ExpNode Execute(ParenthesisOperNode node) => Execute((UOperNode)node);

        /// <summary>
        /// Executes operation on a <see cref="PowOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="PowOperNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="PowOperNode"/>.</returns>
        public virtual ExpNode Execute(PowOperNode node) => Execute((BOperNode)node);

        /// <summary>
        /// Executes operation on a <see cref="RecipricalOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="RecipricalOperNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="RecipricalOperNode"/>.</returns>
        public virtual ExpNode Execute(RecipricalOperNode node) => Execute((UOperNode)node);

        /// <summary>
        /// Executes operation on a <see cref="SineOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="SineOperNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="SineOperNode"/>.</returns>
        public virtual ExpNode Execute(SineOperNode node) => Execute((UOperNode)node);

        /// <summary>
        /// Executes operation on a <see cref="SignOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="SignOperNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="SignOperNode"/>.</returns>
        public virtual ExpNode Execute(SignOperNode node) => Execute((UOperNode)node);

        /// <summary>
        /// Executes operation on a <see cref="TensorNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="TensorNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="TensorNode"/>.</returns>
        public virtual ExpNode Execute(TensorNode node) => Execute((EnumerableCollectionNode)node);

        /// <summary>
        /// Executes operation on a <see cref="UOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="UOperNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="UOperNode"/>.</returns>
        public virtual ExpNode Execute(UOperNode node) => Execute((OperNode)node);

        /// <summary>
        /// Executes operation on a <see cref="VarValueNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="VarValueNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="VarValueNode"/>.</returns>
        public virtual ExpNode Execute(VarValueNode node) => Execute((ValueNode)node);

        /// <summary>
        /// Executes operation on a <see cref="ValueNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="ValueNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="ValueNode"/>.</returns>
        public virtual ExpNode Execute(ValueNode node) => Execute((ExpNode)node);

        /// <summary>
        /// Executes operation on a <see cref="VectorProductOperNode"/>.
        /// </summary>
        /// <param name="node">The <see cref="VectorProductOperNode"/> to execute operation on.</param>
        /// <returns>The result of the operation on a <see cref="VectorProductOperNode"/>.</returns>
        public virtual ExpNode Execute(VectorProductOperNode node) => Execute((BOperNode)node);
    }
}
