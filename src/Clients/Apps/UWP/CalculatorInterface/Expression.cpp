#include "Expression.h"
#include "Expression.g.cpp"

#include "Simplify.h"
#include "InternalPrinter.h"

namespace winrt::CalculatorInterface::implementation
{
    Expression::Expression() {
        parser = new InternalParser();
    }

    Expression::~Expression() {
        delete parser;
    }

    bool Expression::ParseChar(char c)
    {
        return !parser->ParseNextChar(c).Failed();
    }

    void Expression::Clear() {
        delete parser;
        parser = new InternalParser();
    }

    hstring Expression::FinalizeSimplifyPrint() {
        Simplifier* simplify = new Simplifier();
        InternalPrinter* printer = new InternalPrinter();

        parser->Finalize();
        unique_ptr<ExpTree> tree = parser->GetTree();
        string str = tree->Execute(simplify)->Print(*printer);
        return to_hstring(str);
    }
}
