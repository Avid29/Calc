using Calculator.ExpressionTree;
using Calculator.Operations;
using Calculator.Parser.Default;
using Calculator.Parser.Default.Status;
using Calculator.Printers.Default;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Calculator.Tests
{
    public abstract class TestingClass
    {
        private DefaultPrinter _printer;
        private Simplifier _simplifier;

        public TestingClass()
        {
            _printer = new DefaultPrinter();
            _simplifier = new Simplifier();
        }

        protected string Run(string input)
        {
            ExpTree tree;
            ParserStatus result = DefaultParser.Parse(input, out tree);
            Assert.IsFalse(result.Failed);
            return tree.Root.Execute(_simplifier).Print(_printer);
        }
    }
}
