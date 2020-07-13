#pragma once
#include "CalculatorState.g.h"

#include "Simplify.h"
#include "LaTeXParser.h"
#include "LaTeXPrinter.h"
#include "ExpTree.h"

namespace winrt::Calculator::implementation {
	class CalculatorState : public CalculatorStateT<CalculatorState> {
		public:
			CalculatorState();
			~CalculatorState();

			void Clear();
			bool ParseNextChar(char c);

			hstring Simplify();
		private:
			LaTeXParser* parser;
	};
}

namespace winrt::Calculator::factory_implementation
{
	struct CalculatorState : CalculatorStateT<CalculatorState, implementation::CalculatorState>
	{
	};
}