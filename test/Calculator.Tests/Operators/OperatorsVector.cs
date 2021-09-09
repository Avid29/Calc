using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Calculator.Tests.Operators
{
    [TestClass]
    public class OperatorsVector : TestingClass
    {
        [TestMethod]
        public void Addition()
        {
            Assert.IsTrue(Run("<2,2>+<5,5>") == "<7,7>");
        }

        // TODO: Distribute scalar -1 to vector multiplication
        //[TestMethod]
        //public void Subtraction()
        //{
        //    // Assert.IsTrue(Run("<5,5>-<2,2>") == "<3,3>");
        //}
    }
}
