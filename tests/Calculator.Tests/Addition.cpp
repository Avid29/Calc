#include "CppUnitTest.h"

#include "InternalParser.h"
#include "InternalPrinter.h"
#include "Simplify.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests
{
	TEST_CLASS(Tests)
	{
	public:
		Tests() {
			printer = new InternalPrinter();
			simlifier = new Simplifier();
		}

		~Tests() {
			delete printer;
		}

		TEST_METHOD(Add)
		{
			Assert::IsTrue(Run("2+5") == "7");
		}

		TEST_METHOD(Subtract)
		{
			Assert::IsTrue(Run("5-2") == "3");
		}

		TEST_METHOD(Multiply)
		{
			Assert::IsTrue(Run("4*3") == "12");
		}

		TEST_METHOD(Power)
		{
			Assert::IsTrue(Run("3^4") == "81");
		}

		TEST_METHOD(ImpliedMultiply)
		{
			Assert::IsTrue(Run("3(4+5)") == "27");
		}

		TEST_METHOD(ParenthesisDropping)
		{
			Assert::IsTrue(Run("(4+5)") == "9");
		}

		TEST_METHOD(DecimalMultiplyParenthesis)
		{
			Assert::IsTrue(Run("3(4+5)(0.1)") == "2.7");
		}

		TEST_METHOD(MoreDecimalMultiplyParenthesis)
		{
			Assert::IsTrue(Run("(0.1)3(4+5)") == "2.7");
		}

		TEST_METHOD(Variable)
		{
			Assert::IsTrue(Run("x-2") == "x-2");
		}

		TEST_METHOD(MultiplyZeroVariable)
		{
			Assert::IsTrue(Run("(0)3(4x+5)") == "0");
		}

		TEST_METHOD(CombineMultiplicativeTerms)
		{
			Assert::IsTrue(Run("2x*2x") == "4x^2");
		}

		TEST_METHOD(CombineAdditiveTerms)
		{
			Assert::IsTrue(Run("3x+(5x+6x+8xy)") == "14x+8xy");
		}

		TEST_METHOD(DistributiveProperty)
		{
			Assert::IsTrue(Run("3(x+3)") == "3x+9");
		}

		TEST_METHOD(RecursiveDistributiveProperty)
		{
			Assert::IsTrue(Run("(x+3)(x+3)") == "x^2+6x+9");
		}

	private:
		string Run(string str) {
			unique_ptr<ExpTree> tree;
			unique_ptr<ExpTree>* treePtr = &tree;
			Status result = Parse(str, treePtr);
			Assert::IsFalse(result.Failed());
			return tree->Execute(simlifier)->Print(*printer);
		}

		Simplifier* simlifier;
		IPrinter* printer;
	};
}
