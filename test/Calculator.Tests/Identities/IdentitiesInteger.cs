using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Calculator.Tests.Identities
{
    [TestClass]
    public class IdentitiesInteger : TestingClass
    {
        [TestMethod]
        public void Additive()
        {
            Assert.IsTrue(Run("2+0") == "2");
        }

        [TestMethod]
        public void Subtractive()
        {
            Assert.IsTrue(Run("2-2") == "0");
        }

        [TestMethod]
        public void Subtractive0()
        {
            Assert.IsTrue(Run("2-0") == "2");
        }

        [TestMethod]
        public void Multiplicative0()
        {
            Assert.IsTrue(Run("0*2") == "0");
        }

        [TestMethod]
        public void Multiplicative1()
        {
            Assert.IsTrue(Run("1*2") == "2");
        }

        [TestMethod]
        public void Division()
        {
            Assert.IsTrue(Run("2/2") == "1");
        }

        [TestMethod]
        public void Division1()
        {
            Assert.IsTrue(Run("2/1") == "2");
        }

        [TestMethod]
        public void Power0()
        {
            Assert.IsTrue(Run("2^0") == "1");
        }

        [TestMethod]
        public void Power1()
        {
            Assert.IsTrue(Run("2^1") == "2");
        }
    }
}
