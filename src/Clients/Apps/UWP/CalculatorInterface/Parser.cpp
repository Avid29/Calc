#include "pch.h"
#include "Parser.h"
#include "Parser.g.cpp"

namespace winrt::CalculatorInterface::implementation
{
    Parser::Parser() {
        parser = new InternalParser();
    }

    Parser::~Parser() {
        delete parser;
    }

    bool Parser::ParseChar(char c)
    {
        return !parser->ParseNextChar(c).Failed();
    }

    void Parser::Finalize() {
        parser->Finalize();
    }

    Expression Parser::GetResult() {
        return Expression(parser->GetTree());
    }
}
