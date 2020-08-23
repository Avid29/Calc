// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.200703.9

#ifndef WINRT_Windows_Phone_PersonalInformation_1_H
#define WINRT_Windows_Phone_PersonalInformation_1_H
#include "winrt/impl/Windows.Phone.PersonalInformation.0.h"
WINRT_EXPORT namespace winrt::Windows::Phone::PersonalInformation
{
    struct __declspec(empty_bases) IContactAddress :
        Windows::Foundation::IInspectable,
        impl::consume_t<IContactAddress>
    {
        IContactAddress(std::nullptr_t = nullptr) noexcept {}
        IContactAddress(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) IContactChangeRecord :
        Windows::Foundation::IInspectable,
        impl::consume_t<IContactChangeRecord>
    {
        IContactChangeRecord(std::nullptr_t = nullptr) noexcept {}
        IContactChangeRecord(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) IContactInformation :
        Windows::Foundation::IInspectable,
        impl::consume_t<IContactInformation>
    {
        IContactInformation(std::nullptr_t = nullptr) noexcept {}
        IContactInformation(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) IContactInformation2 :
        Windows::Foundation::IInspectable,
        impl::consume_t<IContactInformation2>
    {
        IContactInformation2(std::nullptr_t = nullptr) noexcept {}
        IContactInformation2(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) IContactInformationStatics :
        Windows::Foundation::IInspectable,
        impl::consume_t<IContactInformationStatics>
    {
        IContactInformationStatics(std::nullptr_t = nullptr) noexcept {}
        IContactInformationStatics(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) IContactQueryOptions :
        Windows::Foundation::IInspectable,
        impl::consume_t<IContactQueryOptions>
    {
        IContactQueryOptions(std::nullptr_t = nullptr) noexcept {}
        IContactQueryOptions(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) IContactQueryResult :
        Windows::Foundation::IInspectable,
        impl::consume_t<IContactQueryResult>
    {
        IContactQueryResult(std::nullptr_t = nullptr) noexcept {}
        IContactQueryResult(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) IContactStore :
        Windows::Foundation::IInspectable,
        impl::consume_t<IContactStore>
    {
        IContactStore(std::nullptr_t = nullptr) noexcept {}
        IContactStore(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) IContactStore2 :
        Windows::Foundation::IInspectable,
        impl::consume_t<IContactStore2>
    {
        IContactStore2(std::nullptr_t = nullptr) noexcept {}
        IContactStore2(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) IContactStoreStatics :
        Windows::Foundation::IInspectable,
        impl::consume_t<IContactStoreStatics>
    {
        IContactStoreStatics(std::nullptr_t = nullptr) noexcept {}
        IContactStoreStatics(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) IKnownContactPropertiesStatics :
        Windows::Foundation::IInspectable,
        impl::consume_t<IKnownContactPropertiesStatics>
    {
        IKnownContactPropertiesStatics(std::nullptr_t = nullptr) noexcept {}
        IKnownContactPropertiesStatics(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) IStoredContact :
        Windows::Foundation::IInspectable,
        impl::consume_t<IStoredContact>,
        impl::require<Windows::Phone::PersonalInformation::IStoredContact, Windows::Phone::PersonalInformation::IContactInformation>
    {
        IStoredContact(std::nullptr_t = nullptr) noexcept {}
        IStoredContact(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) IStoredContactFactory :
        Windows::Foundation::IInspectable,
        impl::consume_t<IStoredContactFactory>
    {
        IStoredContactFactory(std::nullptr_t = nullptr) noexcept {}
        IStoredContactFactory(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
}
#endif
