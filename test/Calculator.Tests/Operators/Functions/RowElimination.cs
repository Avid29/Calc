using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Calculator.Tests.Operators.Functions
{
    [TestClass]
    public class RowElimination : TestingClass
    {
        [TestMethod]
        public void GaussIdentity3x2()
        {
            Assert.IsTrue(Run(@"\ref{\matrix[3,2]{1,0,2,0,1,3}}") == @"\matrix[3,2]{1,0,2,0,1,3}");
        }

        [TestMethod]
        public void GaussInt3x2()
        {
            Assert.IsTrue(Run(@"\ref{\matrix[3,2]{2,3,16,4,2,16}}") == @"\matrix[3,2]{1,1.5,8,0,1,4}");
        }

        [TestMethod]
        public void GaussJordanInt3x2()
        {
            Assert.IsTrue(Run(@"\rref{\matrix[3,2]{2,3,16,4,2,16}}") == @"\matrix[3,2]{1,0,2,0,1,4}");
        }

        [TestMethod]
        public void GaussJordanVar3x2()
        {
            Assert.IsTrue(Run(@"\rref{\matrix[3,2]{2,3,16z,4,2,16z}}") == @"\matrix[3,2]{1,0,2z,0,1,4z}");
        }

        [TestMethod]
        public void GaussJordanIdentity3x2()
        {
            Assert.IsTrue(Run(@"\rref{\matrix[3,2]{1,0,2,0,1,3}}") == @"\matrix[3,2]{1,0,2,0,1,3}");
        }
    }
}
