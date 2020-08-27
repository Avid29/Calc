#include "CppUnitTest.h"

#include "InternalParser.h"
#include "InternalPrinter.h"
#include "Simplify.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests {
	namespace Operators {
		TEST_CLASS(OperatorsVariable)
		{
		public:
			OperatorsVariable() {
				printer = new InternalPrinter();
				simlifier = new Simplifier();
			}

			~OperatorsVariable() {
				delete printer;
			}

			TEST_METHOD(Addition)
			{
				Assert::IsTrue(Run("2x+x") == "3x");
			}

			TEST_METHOD(Subtraction)
			{
				// TODO: Symbolic subtraction
				//Assert::IsTrue(Run("2x-x") == "x");
			}

			TEST_METHOD(Multiplication)
			{
				Assert::IsTrue(Run("4x*3x") == "12x^2");
			}

			TEST_METHOD(Power)
			{
				Assert::IsTrue(Run("3x^4") == "3x^4");
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
