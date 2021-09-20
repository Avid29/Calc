using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators.Functions;
using Calculator.Operations;
using Calculator.Parser.Default;
using Calculator.Printers.Default;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Calculator.Tests.Operators.Functions
{
    [TestClass]
    public class VectorProjections : TestingClass
    {
        [TestMethod]
        public void VectorProj()
        {
            // Parse
            DefaultParser parser = new DefaultParser();
            VectorProjOperNode node = new VectorProjOperNode();
            parser.ParseString("<4,2,2>");
            node.AddChild(parser.Tree.Root);
            parser = new DefaultParser();
            parser.ParseString("<2,6,4>");
            node.AddChild(parser.Tree.Root);

            // Simplify
            Simplifier simplifier = new Simplifier();
            ExpNode exp_result = node.Execute(simplifier);

            // Print
            DefaultPrinter printer = new DefaultPrinter();
            string str_result = exp_result.Print(printer);

            // Compare
            Assert.IsTrue(str_result == "<1,3,2>");
        }
    }
}
