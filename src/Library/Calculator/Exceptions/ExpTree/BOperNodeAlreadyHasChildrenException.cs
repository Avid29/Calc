﻿using Calculator.ExpTree.Nodes.Operators;

namespace Calculator.Exceptions.ExpTree
{
    public class BOperNodeAlreadyHasChildrenException : ExpNodeException
    {
        private const string MESSAGE = "Cannot add child to BOperNode because it already contains a two (2) children";

        public BOperNodeAlreadyHasChildrenException(BOperNode node) : base(node, MESSAGE) { }
    }
}
