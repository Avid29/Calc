using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Calculator.Tests.Identities
{
    [TestClass]
    public class IdentitiesFloat : TestingClass
    {
        [TestMethod]
        public void Additive()
        {
            Assert.IsTrue(Run("1.5+0") == "1.5");
        }

        [TestMethod]
        public void Subtractive()
        {
            Assert.IsTrue(Run("1.5-1.5") == "0");
        }

        [TestMethod]
        public void Subtractive0()
        {
            Assert.IsTrue(Run("1.5-0") == "1.5");
        }

        [TestMethod]
        public void Multiplicative0()
        {
            Assert.IsTrue(Run("0*1.5") == "0");
        }

        [TestMethod]
        public void Multiplicative1()
        {
            Assert.IsTrue(Run("1*1.5") == "1.5");
        }

        [TestMethod]
        public void Division()
        {
            Assert.IsTrue(Run("1.5/1.5") == "1");
        }

        [TestMethod]
        public void Division1()
        {
            Assert.IsTrue(Run("1.5/1") == "1.5");
        }

        [TestMethod]
        public void Power0()
        {
            Assert.IsTrue(Run("1.5^0") == "1");
        }

        [TestMethod]
        public void Power1()
        {
            Assert.IsTrue(Run("1.5^1") == "1.5");
        }
    }
}
