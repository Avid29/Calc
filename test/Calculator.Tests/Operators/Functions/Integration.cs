// Adam Dernis 2024

using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Calculator.Tests.Operators.Functions;

[TestClass]
public class Integration : TestingClass
{
    [TestMethod]
    public void ConstantRule() => Assert.IsTrue(Run(@"\int[x]{2}") == "2x");

    [TestMethod]
    public void AdditiveRule() => Assert.IsTrue(Run(@"\int[x]{2x+2}") == "2x+x^2"); // TODO: Sort A terms
}
