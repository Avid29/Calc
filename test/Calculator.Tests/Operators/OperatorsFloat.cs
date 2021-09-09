using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Calculator.Tests.Operators
{
    [TestClass]
    public class OperatorsFloat : TestingClass
    {
        [TestMethod]
        public void Addition()
        {
            Assert.IsTrue(Run("2.2+5.5") == "7.7");
        }

        [TestMethod]
        public void Subtraction()
        {
            Assert.IsTrue(Run("5.5-2.2") == "3.3");
        }

        [TestMethod]
        public void Multiplication()
        {
            Assert.IsTrue(Run("4.4*3.3") == "14.52");
        }

        [TestMethod]
        public void PowerBase()
        {
            Assert.IsTrue(Run("1.5^2") == "2.25");
        }
    }
}
