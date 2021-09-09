using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Calculator.Tests.Operators
{
    [TestClass]
    public class OperatorsVariable : TestingClass
    {
        [TestMethod]
        public void Addition()
        {
            Assert.IsTrue(Run("2x+x") == "3x");
        }

        [TestMethod]
        public void Subtraction()
        {
            Assert.IsTrue(Run("2x-x") == "x");
        }

        [TestMethod]
        public void Multiplication()
        {
            Assert.IsTrue(Run("4x*3x") == "12x^2");
        }

        [TestMethod]
        public void Power()
        {
            Assert.IsTrue(Run("3x^4") == "3x^4");
        }
    }
}
