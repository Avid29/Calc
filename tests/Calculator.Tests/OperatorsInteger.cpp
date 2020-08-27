#include "CppUnitTest.h"

#include "InternalParser.h"
#include "InternalPrinter.h"
#include "Simplify.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests {
	namespace Operators {
		TEST_CLASS(OperatorsInteger)
		{
		public:
			OperatorsInteger() {
				printer = new InternalPrinter();
				simlifier = new Simplifier();
			}

			~OperatorsInteger() {
				delete printer;
			}

			TEST_METHOD(Addition)
			{
				Assert::IsTrue(Run("2+5") == "7");
			}

			TEST_METHOD(Subtraction)
			{
				Assert::IsTrue(Run("5-2") == "3");
			}

			TEST_METHOD(Multiplication)
			{
				Assert::IsTrue(Run("4*3") == "12");
			}

			TEST_METHOD(Power)
			{
				Assert::IsTrue(Run("3^4") == "81");
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
