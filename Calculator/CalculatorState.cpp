#include <Unknwn.h>
#include <winrt/base.h>
#include <stringapiset.h>

#include "CalculatorState.h"

namespace winrt::Calculator::implementation {
	CalculatorState::CalculatorState() {
		Clear();
	}

	CalculatorState::~CalculatorState() {
		delete parser;
	}

	void CalculatorState::Clear() {
		delete parser;
		parser = new LaTeXParser();
	}

	bool CalculatorState::ParseNextChar(char c) {
		return parser->ParseNextChar(c);
	}

	hstring CalculatorState::Simplify() {
		Simplifier* simplifier = new Simplifier();
		LaTeXPrinter* printer = new LaTeXPrinter();
		string result = parser->FinalizeAndReturn()->Execute(simplifier)->Print(*printer);
		delete simplifier;
		delete printer;
		Clear();
		return to_hstring(result);;
	}
};