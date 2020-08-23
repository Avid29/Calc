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
		parser = new InternalParser();
	}

	bool CalculatorState::ParseNextChar(char c) {
		return !parser->ParseNextChar(c).Occured();
	}

	hstring CalculatorState::Simplify() {
		Simplifier* simplifier = new Simplifier();
		InternalPrinter* printer = new InternalPrinter();
		string result = parser->FinalizeAndReturn()->Execute(simplifier)->Print(*printer);
		delete simplifier;
		delete printer;
		Clear();
		return to_hstring(result);;
	}
};