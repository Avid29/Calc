#include "CppUnitTest.h"

#include "InternalParser.h"
#include "InternalPrinter.h"
#include "Simplify.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests {
	namespace Operators {
		TEST_CLASS(OperatorsFloat)
		{
		public:
			OperatorsFloat() {
				printer = new InternalPrinter();
				simlifier = new Simplifier();
			}

			~OperatorsFloat() {
				delete printer;
			}

			TEST_METHOD(Addition)
			{
				Assert::IsTrue(Run("2.2+5.5") == "7.7");
			}

			TEST_METHOD(Subtraction)
			{
				Assert::IsTrue(Run("5.5-2.2") == "3.3");
			}

			TEST_METHOD(Multiplication)
			{
				Assert::IsTrue(Run("4.4*3.3") == "14.52");
			}

			TEST_METHOD(PowerBase)
			{
				Assert::IsTrue(Run("1.5^2") == "2.25");
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
