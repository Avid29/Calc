#pragma once

#include "Expression.g.h"
#include "InternalParser.h"

namespace winrt::CalculatorInterface::implementation
{
    struct Expression : ExpressionT<Expression>
    {
    public:
        Expression();
        ~Expression();
        bool ParseChar(char c);
        hstring FinalizeSimplifyPrint();
    private:
        InternalParser *parser;
    };
}

namespace winrt::CalculatorInterface::factory_implementation
{
    struct Expression : ExpressionT<Expression, implementation::Expression>
    {
    };
}
