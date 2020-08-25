#include "Expression.h"

#include "Simplify.h"

namespace winrt::CalculatorInterface::implementation {
	Expression::Expression(unique_ptr<ExpTree> rootNode) {
		root_node = rootNode->GetRoot();
	}

	void Expression::Execute(IOperation *operation) {
		bool defaultOperation = operation == nullptr;
		if (defaultOperation) {
			operation = new Simplifier();
		}

		root_node = root_node->Execute(operation);

		if (defaultOperation) {
			delete operation;
		}
	}

	hstring Expression::Print(IPrinter *printer) {
		bool defaultOperation = printer == nullptr;
		if (defaultOperation) {
			printer = new InternalPrinter();
		}

		string result = root_node->Print(*printer);

		if (defaultOperation) {
			delete printer;
		}

		return to_hstring(result);
	}
}
