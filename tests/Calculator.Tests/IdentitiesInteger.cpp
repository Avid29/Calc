#include "CppUnitTest.h"

#include "InternalParser.h"
#include "InternalPrinter.h"
#include "Simplify.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests {
	namespace Identities {
		TEST_CLASS(IdentitiesInteger)
		{
		public:
			IdentitiesInteger() {
				printer = new InternalPrinter();
				simlifier = new Simplifier();
			}

			~IdentitiesInteger() {
				delete printer;
			}

			TEST_METHOD(AdditiveIntIdentity)
			{
				Assert::IsTrue(Run("1+0") == "1");
			}

			TEST_METHOD(SubtractiveIntIdentity)
			{
				Assert::IsTrue(Run("1-0") == "1");
			}

			TEST_METHOD(MultiplicativeIntIdentity)
			{
				Assert::IsTrue(Run("0*1") == "0");
			}

			TEST_METHOD(DivisionIntIdentity)
			{
				Assert::IsTrue(Run("1/1") == "1");
			}

			TEST_METHOD(PowerInt0Identity)
			{
				Assert::IsTrue(Run("2^0") == "1");
			}

			TEST_METHOD(PowerInt1Identity)
			{
				Assert::IsTrue(Run("2^1") == "2");
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
