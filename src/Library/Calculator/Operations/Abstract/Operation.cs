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

namespace Calculator.Operations.Abstract
{
    public abstract class Operation
    {
        public virtual ExpNode Execute(AdditionOperNode node) => Execute((NOperNode)node);

        public virtual ExpNode Execute(BranchNode node) => Execute((ExpNode)node);

        public virtual ExpNode Execute(BOperNode node) => Execute((OperNode)node);

        public virtual ExpNode Execute(DiffOperNode node) => Execute((OperNode)node);

        public virtual ExpNode Execute(EnumerableCollectionNode node) => Execute((BranchNode)node);

        public abstract ExpNode Execute(ExpNode node);

        public virtual ExpNode Execute(FloatValueNode node) => Execute((NumericalValueNode)node);

        public virtual ExpNode Execute(IntegralOperNode node) => Execute((OperNode)node);

        public virtual ExpNode Execute(IntValueNode node) => Execute((NumericalValueNode)node);

        public virtual ExpNode Execute(MultiplicationOperNode node) => Execute((NOperNode)node);

        public virtual ExpNode Execute(NOperNode node) => Execute((OperNode)node);

        public virtual ExpNode Execute(NumericalValueNode node) => Execute((ValueNode)node);

        public virtual ExpNode Execute(OperNode node) => Execute((BranchNode)node);

        public virtual ExpNode Execute(ParenthesisOperNode node) => Execute((UOperNode)node);

        public virtual ExpNode Execute(PowOperNode node) => Execute((BOperNode)node);

        public virtual ExpNode Execute(RecipricalOperNode node) => Execute((UOperNode)node);

        public virtual ExpNode Execute(SineOperNode node) => Execute((UOperNode)node);

        public virtual ExpNode Execute(SignOperNode node) => Execute((UOperNode)node);

        public virtual ExpNode Execute(TensorNode node) => Execute((EnumerableCollectionNode)node);

        public virtual ExpNode Execute(UOperNode node) => Execute((OperNode)node);

        public virtual ExpNode Execute(VarValueNode node) => Execute((ValueNode)node);

        public virtual ExpNode Execute(ValueNode node) => Execute((ExpNode)node);
    }
}
