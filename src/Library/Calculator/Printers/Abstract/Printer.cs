using Calculator.ExpTree.Nodes;
using Calculator.ExpTree.Nodes.Collections;
using Calculator.ExpTree.Nodes.Operators;
using Calculator.ExpTree.Nodes.Operators.BOpers;
using Calculator.ExpTree.Nodes.Operators.Functions;
using Calculator.ExpTree.Nodes.Operators.NOpers;
using Calculator.ExpTree.Nodes.Operators.UOpers;
using Calculator.ExpTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpTree.Nodes.Operators.UOpers.SineNode;
using Calculator.ExpTree.Nodes.Values;

namespace Calculator.Printers.Abstract
{
    public abstract class Printer
    {
        public virtual string Print(AdditionOperNode node) => Print((NOperNode)node);

        public virtual string Print(BranchNode node) => Print((ExpNode)node);

        public virtual string Print(BOperNode node) => Print((OperNode)node);

        public virtual string Print(DiffOperNode node) => Print((OperNode)node);

        public virtual string Print(EnumerableCollectionNode node) => Print((BranchNode)node);

        public abstract string Print(ExpNode node);

        public virtual string Print(FloatValueNode node) => Print((ValueNode)node);

        public virtual string Print(IntegralOperNode node) => Print((OperNode)node);

        public virtual string Print(IntValueNode node) => Print((ValueNode)node);

        public virtual string Print(MultiplicationOperNode node) => Print((NOperNode)node);

        public virtual string Print(NOperNode node) => Print((OperNode)node);

        public virtual string Print(OperNode node) => Print((BranchNode)node);

        public virtual string Print(ParenthesisOperNode node) => Print((UOperNode)node);

        public virtual string Print(PowOperNode node) => Print((BOperNode)node);

        public virtual string Print(SineOperNode node) => Print((UOperNode)node);

        public virtual string Print(SignOperNode node) => Print((UOperNode)node);

        public virtual string Print(TensorNode node) => Print((EnumerableCollectionNode)node);

        public virtual string Print(UOperNode node) => Print((OperNode)node);

        public virtual string Print(VarValueNode node) => Print((ValueNode)node);

        public virtual string Print(ValueNode node) => Print((ExpNode)node);
    }
}
