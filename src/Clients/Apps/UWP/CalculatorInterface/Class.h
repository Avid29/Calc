#pragma once

#include "Class.g.h"

namespace winrt::CalculatorInterface::implementation
{
    struct Class : ClassT<Class>
    {
        Class() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::CalculatorInterface::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
}
