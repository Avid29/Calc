#include "CppUnitTest.h"

#include "InternalParser.h"
#include "InternalPrinter.h"
#include "Simplify.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests {
	namespace Identities {
		TEST_CLASS(IdentitiesVariable)
		{
		public:
			IdentitiesVariable() {
				printer = new InternalPrinter();
				simlifier = new Simplifier();
			}

			~IdentitiesVariable() {
				delete printer;
			}

			TEST_METHOD(AdditiveVarIdentity)
			{
				Assert::IsTrue(Run("x+0") == "x");
			}

			TEST_METHOD(SubtractiveVarIdentity)
			{
				Assert::IsTrue(Run("x-0") == "x");
			}

			TEST_METHOD(MultiplicativeVarIdentity)
			{
				Assert::IsTrue(Run("0*x") == "0");
			}

			TEST_METHOD(DivisionVarIdentity)
			{
				Assert::IsTrue(Run("x/x") == "1");
			}

			TEST_METHOD(PowerVar0Identity)
			{
				Assert::IsTrue(Run("x^0") == "1");
			}

			TEST_METHOD(PowerVar1Identity)
			{
				Assert::IsTrue(Run("x^1") == "x");
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
}
