// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.200703.9

#ifndef WINRT_Calculator_H
#define WINRT_Calculator_H
#include "winrt/base.h"
static_assert(winrt::check_version(CPPWINRT_VERSION, "2.0.200703.9"), "Mismatched C++/WinRT headers.");
#include "winrt/impl/Calculator.2.h"
namespace winrt::impl
{
    template <typename D> WINRT_IMPL_AUTO(void) consume_Calculator_ICalculatorState<D>::Clear() const
    {
        check_hresult(WINRT_IMPL_SHIM(Calculator::ICalculatorState)->Clear());
    }
    template <typename D> WINRT_IMPL_AUTO(bool) consume_Calculator_ICalculatorState<D>::ParseNextChar(char16_t c) const
    {
        bool result{};
        check_hresult(WINRT_IMPL_SHIM(Calculator::ICalculatorState)->ParseNextChar(c, &result));
        return result;
    }
    template <typename D> WINRT_IMPL_AUTO(hstring) consume_Calculator_ICalculatorState<D>::Simplify() const
    {
        void* result{};
        check_hresult(WINRT_IMPL_SHIM(Calculator::ICalculatorState)->Simplify(&result));
        return hstring{ result, take_ownership_from_abi };
    }
    template <typename D>
    struct produce<D, Calculator::ICalculatorState> : produce_base<D, Calculator::ICalculatorState>
    {
        int32_t __stdcall Clear() noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            this->shim().Clear();
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall ParseNextChar(char16_t c, bool* result) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *result = detach_from<bool>(this->shim().ParseNextChar(c));
            return 0;
        }
        catch (...) { return to_hresult(); }
        int32_t __stdcall Simplify(void** result) noexcept final try
        {
            clear_abi(result);
            typename D::abi_guard guard(this->shim());
            *result = detach_from<hstring>(this->shim().Simplify());
            return 0;
        }
        catch (...) { return to_hresult(); }
    };
}
WINRT_EXPORT namespace winrt::Calculator
{
    inline CalculatorState::CalculatorState() :
        CalculatorState(impl::call_factory_cast<CalculatorState(*)(Windows::Foundation::IActivationFactory const&), CalculatorState>([](Windows::Foundation::IActivationFactory const& f) { return f.template ActivateInstance<CalculatorState>(); }))
    {
    }
}
namespace std
{
#ifndef WINRT_LEAN_AND_MEAN
    template<> struct hash<winrt::Calculator::ICalculatorState> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Calculator::CalculatorState> : winrt::impl::hash_base {};
#endif
}
#endif
