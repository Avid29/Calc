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
		return parser->ParseNextChar(c);
	}

	int CalculatorState::ParseString(string str) {
		for (size_t i = 0; i < str.size(); i++)
		{
			if (!ParseNextChar(str[i])) {
				return i;
			}
		}
		return -1;
	}

	hstring CalculatorState::Simplify() {
		Simplifier* simplifier = new Simplifier();
		InternalPrinter* internalPrinter = new InternalPrinter();
		DisplayPrinter* displayPrinter = new DisplayPrinter(true);
		unique_ptr<ExpNode> expression = parser->FinalizeAndReturn()->Execute(simplifier);
		string result = expression->Print(*displayPrinter);
		Clear();
		ParseString(expression->Print(*internalPrinter));
		delete simplifier;
		delete internalPrinter;
		delete displayPrinter;
		return to_hstring(result);
	}

	hstring CalculatorState::GetDisplay() {
		DisplayPrinter* printer = new DisplayPrinter(false);
		string display = parser->GetProgress(*printer);
		delete printer;
		return to_hstring(display);
	}
};
