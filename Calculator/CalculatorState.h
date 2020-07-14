#pragma once
#include "CalculatorState.g.h"

#include "Simplify.h"
#include "InternalParser.h"
#include "InternalPrinter.h"
#include "DisplayPrinter.h"
#include "ExpTree.h"

namespace winrt::Calculator::implementation {
	class CalculatorState : public CalculatorStateT<CalculatorState> {
		public:
			CalculatorState();
			~CalculatorState();

			void Clear();
			bool ParseNextChar(char c);

			hstring Simplify();

			hstring GetDisplay();
		private:
			int ParseString(string str);

			InternalParser* parser;
	};
}

namespace winrt::Calculator::factory_implementation
{
	struct CalculatorState : CalculatorStateT<CalculatorState, implementation::CalculatorState>
	{
	};
}