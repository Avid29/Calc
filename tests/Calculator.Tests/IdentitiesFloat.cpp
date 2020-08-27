#include "CppUnitTest.h"

#include "InternalParser.h"
#include "InternalPrinter.h"
#include "Simplify.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests {
	namespace Identities {
		TEST_CLASS(IdentitiesFloat)
		{
		public:
			IdentitiesFloat() {
				printer = new InternalPrinter();
				simlifier = new Simplifier();
			}

			~IdentitiesFloat() {
				delete printer;
			}

			TEST_METHOD(AdditiveFloatIdentity)
			{
				Assert::IsTrue(Run("1.5+0") == "1.5");
			}

			TEST_METHOD(SubtractiveFloatIdentity)
			{
				Assert::IsTrue(Run("1.5-0") == "1.5");
			}

			TEST_METHOD(MultiplicativeFloatIdentity)
			{
				Assert::IsTrue(Run("0*1.5") == "0");
			}

			TEST_METHOD(DivisionFloatIdentity)
			{
				Assert::IsTrue(Run("1.5/1.5") == "1");
			}

			TEST_METHOD(Power0Identity)
			{
				Assert::IsTrue(Run("1.5^0") == "1");
			}

			TEST_METHOD(Power1Identity)
			{
				Assert::IsTrue(Run("1.5^1") == "1.5");
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
