using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Calculator.Tests.Operators.Functions
{
    [TestClass]
    public class PartialDerivatives : TestingClass
    {
        [TestMethod]
        public void ConstantRule()
        {
            Assert.IsTrue(Run(@"\diff[x]{5y^5}") == "0");
        }

        [TestMethod]
        public void AdditiveRule()
        {
            Assert.IsTrue(Run(@"\diff[x]{x^2 + 2x + 3}") == "2x+2");
        }

        [TestMethod]
        public void ProductRule()
        {
            Assert.IsTrue(Run(@"\diff[x]{2x^2 * y}") == "4xy");
            // Assert::IsTrue(Run(@"\diff[x]{2xy}") == "2y + 2x\diff[x]{y}"); // TODO: Better partial derivatives
        }

        [TestMethod]
        public void PowerRule()
        {
            Assert.IsTrue(Run(@"\diff[x]{5x^5}") == "25x^4");
        }
    }
}
