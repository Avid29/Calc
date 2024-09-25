// Adam Dernis 2024

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators.Functions.VectorProduct;
using Calculator.Operations;
using Calculator.Parser.Default;
using Calculator.Printers.Default;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Calculator.Tests.Operators.Functions;

[TestClass]
public class VectorProducts : TestingClass
{
    [TestMethod]
    public void DotProduct()
    {
        // Parse
        DefaultParser parser = new();
        VectorProductOperNode node = new(VectorProductMethod.Dot);
        parser.ParseString("<2,1,3>");
        node.AddChild(parser.Tree.Root);
        parser = new DefaultParser();
        parser.ParseString("<1,2,3>");
        node.AddChild(parser.Tree.Root);

        // Simplify
        Simplifier simplifier = new();
        ExpNode exp_result = node.Execute(simplifier);

        // Print
        DefaultPrinter printer = new();
        string str_result = exp_result.Print(printer);

        // Compare
        Assert.IsTrue(str_result == "13");
    }
}
