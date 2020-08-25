#pragma once

#include <winrt/Windows.Foundation.h>

#include "ExpNode.h"
#include "InternalPrinter.h"

namespace winrt::CalculatorInterface::implementation {
	struct Expression
	{
	public:
		Expression(unique_ptr<ExpTree> rootNode);

		void Execute(IOperation* operation = nullptr);

		hstring Print(IPrinter* printer = nullptr);
		 
	private:
		unique_ptr<ExpNode> root_node;
	};
}
