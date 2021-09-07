﻿using Calculator.Operations.Abstract;
using Calculator.Printers.Abstract;

namespace Calculator.ExpTree.Nodes.Operators.NOpers
{
    public class MultiplicationOperNode : NOperNode
    {
        public override Priority Priority => Priority.MULTIPLICATION;

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
