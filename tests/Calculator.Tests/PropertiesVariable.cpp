#include "CppUnitTest.h"

#include "InternalParser.h"
#include "InternalPrinter.h"
#include "Simplify.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests {
	namespace Properties {
		TEST_CLASS(PropertiesVariable)
		{
		public:
			PropertiesVariable() {
				printer = new InternalPrinter();
				simlifier = new Simplifier();
			}

			~PropertiesVariable() {
				delete printer;
			}

			TEST_METHOD(MultiplyDistributive)
			{
				Assert::IsTrue(Run("2(x+1)") == "2x+2");
			}

			TEST_METHOD(PowerDistributive)
			{
				Assert::IsTrue(Run("(2x)^2") == "4x^2");
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
