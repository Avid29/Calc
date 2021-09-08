using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Calculator.Tests.Distributive
{
    [TestClass]
    public class Distributive : TestingClass
    {
        [TestMethod]
        public void MultiplicativeDistributive()
        {
            Assert.IsTrue(Run("2(x+1)") == "2x+2");
        }

        [TestMethod]
        public void PowerDistributive()
        {
            Assert.IsTrue(Run("(2x)^2") == "4x^2");
        }
    }
}
