using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Calculator.Tests.Operators
{
    [TestClass]
    public class OperatorsInteger : TestingClass
    {
        [TestMethod]
        public void Addition()
        {
            Assert.IsTrue(Run("2+5") == "7");
        }

        [TestMethod]
        public void Subtraction()
        {
            Assert.IsTrue(Run("5-2") == "3");
        }

        [TestMethod]
        public void Multiplication()
        {
            Assert.IsTrue(Run("4*3") == "12");
        }

        [TestMethod]
        public void Power()
        {
            Assert.IsTrue(Run("3^4") == "81");
        }
    }
}
