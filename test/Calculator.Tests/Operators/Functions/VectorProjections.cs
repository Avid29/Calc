using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Calculator.Tests.Operators.Functions
{
    [TestClass]
    public class VectorProjections : TestingClass
    {
        [TestMethod]
        public void VectorProj()
        {
            Assert.IsTrue(Run(@"\proj{<4,2,2>, <2,6,4>}") == "<1,3,2>");
        }
    }
}
