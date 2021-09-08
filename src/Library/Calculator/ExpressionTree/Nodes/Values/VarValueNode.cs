﻿using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpressionTree.Nodes.Values
{
    public class VarValueNode : ValueNode
    {
        public VarValueNode(VarValueNode node)
        {
            Character = node.Character;
        }

        public VarValueNode(char c)
        {
            Character = c;
        }

        public char Character { get; }

        public override ExpNode Clone()
        {
            return new VarValueNode(this);
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