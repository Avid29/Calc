#pragma once

#include "InternalParser.h"
#include "Expression.h"
#include "Parser.g.h"

namespace winrt::CalculatorInterface::implementation
{
    struct Parser : ParserT<Parser>
    {
    public:
        Parser();
        ~Parser();
        bool ParseChar(char c);

        void Finalize();

        Expression GetResult();
    private:
        InternalParser *parser;
    };
}

namespace winrt::CalculatorInterface::factory_implementation
{
    struct Parser : ParserT<Parser, implementation::Parser>
    {
    };
}
