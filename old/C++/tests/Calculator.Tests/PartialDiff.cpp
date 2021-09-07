#include "CppUnitTest.h"

#include "InternalParser.h"
#include "InternalPrinter.h"
#include "Simplify.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests {
	namespace Operators {
		TEST_CLASS(PartialDiff)
		{
		public:
			PartialDiff() {
				printer = new InternalPrinter();
				simlifier = new Simplifier();
			}

			~PartialDiff() {
				delete printer;
			}

			TEST_METHOD(PowerRule)
			{
				Assert::IsTrue(Run("\\diff[x]{5x^5}") == "25x^4");
			}

			TEST_METHOD(AdditionRule)
			{
				Assert::IsTrue(Run("\\diff[x]{x^2 + 2x + 3}") == "2x+2");
			}

			TEST_METHOD(ProductRule)
			{
				Assert::IsTrue(Run("\\diff[x]{2x^2 * y}") == "4xy");
				//Assert::IsTrue(Run("\\diff[x]{2xy}") == "2y + 2x\\diff[x]{y}"); // TODO: Better partial derivatives
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
