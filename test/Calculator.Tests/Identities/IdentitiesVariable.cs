using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Calculator.Tests.Identities
{
    [TestClass]
    public class IdentitiesVariable : TestingClass
    {
        [TestMethod]
        public void Additive()
        {
            Assert.IsTrue(Run("x+0") == "x");
        }

        [TestMethod]
        public void Subtractive()
        {
            Assert.IsTrue(Run("x-x") == "0");
        }

        [TestMethod]
        public void Subtractive0()
        {
            Assert.IsTrue(Run("x-0") == "x");
        }

        [TestMethod]
        public void Multiplicative0()
        {
            Assert.IsTrue(Run("0*x") == "0");
        }

        [TestMethod]
        public void Multiplicative1()
        {
            Assert.IsTrue(Run("x*1") == "x");
        }

        [TestMethod]
        public void Division()
        {
            Assert.IsTrue(Run("x/x") == "1");
        }

        [TestMethod]
        public void Division1()
        {
            Assert.IsTrue(Run("x/1") == "x");
        }

        [TestMethod]
        public void Power0()
        {
            Assert.IsTrue(Run("x^0") == "1");
        }

        [TestMethod]
        public void Power1()
        {
            Assert.IsTrue(Run("x^1") == "x");
        }
    }
}
