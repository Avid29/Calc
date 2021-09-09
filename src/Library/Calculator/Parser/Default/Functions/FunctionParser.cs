﻿// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.Parser.Default.Status;

namespace Calculator.Parser.Default.Functions
{
    public abstract class FunctionParser
    {
        protected int _depth = 0;

        public BranchNode Output { get; protected set; }

        public static FunctionParser MakeFunctionParser(char c)
        {
            switch (c)
            {
                case '<':
                    return new VectorParser();
                default:
                    return null;
            }
        }

        public static FunctionParser MakeFunctionParser(string functionName)
        {
            switch (functionName)
            {
                case "sin":
                case "cos":
                case "tan":
                case "csc":
                case "sec":
                case "cot":
                    return new SinusoidalFuncParser(functionName);
                case "diff":
                    return new DiffFuncParser();
                case "int":
                    return new IntegralFuncParser();
                default:
                    return null;
            }
        }

        public abstract ParseError ParseFirstChar(char c);

        public abstract ParseError ParseNextChar(char c);
    }
}
