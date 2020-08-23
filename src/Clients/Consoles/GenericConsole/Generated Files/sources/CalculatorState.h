#pragma once
#include "CalculatorState.g.h"

// Note: Remove this static_assert after copying these generated source files to your project.
// This assertion exists to avoid compiling these generated source files directly.
static_assert(false, "Do not compile generated C++/WinRT source files directly");

namespace winrt::Calculator::implementation
{
    struct CalculatorState : CalculatorStateT<CalculatorState>
    {
        CalculatorState() = default;

        void Clear();
        bool ParseNextChar(char16_t c);
        hstring Simplify();
    };
}
namespace winrt::Calculator::factory_implementation
{
    struct CalculatorState : CalculatorStateT<CalculatorState, implementation::CalculatorState>
    {
    };
}
