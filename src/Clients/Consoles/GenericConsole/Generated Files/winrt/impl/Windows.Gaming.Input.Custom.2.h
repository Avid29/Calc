// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.200703.9

#ifndef WINRT_Windows_Gaming_Input_Custom_2_H
#define WINRT_Windows_Gaming_Input_Custom_2_H
#include "winrt/impl/Windows.Gaming.Input.1.h"
#include "winrt/impl/Windows.Gaming.Input.Custom.1.h"
WINRT_EXPORT namespace winrt::Windows::Gaming::Input::Custom
{
    struct GameControllerVersionInfo
    {
        uint16_t Major;
        uint16_t Minor;
        uint16_t Build;
        uint16_t Revision;
    };
    inline bool operator==(GameControllerVersionInfo const& left, GameControllerVersionInfo const& right) noexcept
    {
        return left.Major == right.Major && left.Minor == right.Minor && left.Build == right.Build && left.Revision == right.Revision;
    }
    inline bool operator!=(GameControllerVersionInfo const& left, GameControllerVersionInfo const& right) noexcept
    {
        return !(left == right);
    }
    struct GipFirmwareUpdateProgress
    {
        double PercentCompleted;
        uint32_t CurrentComponentId;
    };
    inline bool operator==(GipFirmwareUpdateProgress const& left, GipFirmwareUpdateProgress const& right) noexcept
    {
        return left.PercentCompleted == right.PercentCompleted && left.CurrentComponentId == right.CurrentComponentId;
    }
    inline bool operator!=(GipFirmwareUpdateProgress const& left, GipFirmwareUpdateProgress const& right) noexcept
    {
        return !(left == right);
    }
    struct GameControllerFactoryManager
    {
        GameControllerFactoryManager() = delete;
        static auto RegisterCustomFactoryForGipInterface(Windows::Gaming::Input::Custom::ICustomGameControllerFactory const& factory, winrt::guid const& interfaceId);
        static auto RegisterCustomFactoryForHardwareId(Windows::Gaming::Input::Custom::ICustomGameControllerFactory const& factory, uint16_t hardwareVendorId, uint16_t hardwareProductId);
        static auto RegisterCustomFactoryForXusbType(Windows::Gaming::Input::Custom::ICustomGameControllerFactory const& factory, Windows::Gaming::Input::Custom::XusbDeviceType const& xusbType, Windows::Gaming::Input::Custom::XusbDeviceSubtype const& xusbSubtype);
        static auto TryGetFactoryControllerFromGameController(Windows::Gaming::Input::Custom::ICustomGameControllerFactory const& factory, Windows::Gaming::Input::IGameController const& gameController);
    };
    struct __declspec(empty_bases) GipFirmwareUpdateResult : Windows::Gaming::Input::Custom::IGipFirmwareUpdateResult
    {
        GipFirmwareUpdateResult(std::nullptr_t) noexcept {}
        GipFirmwareUpdateResult(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Gaming::Input::Custom::IGipFirmwareUpdateResult(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) GipGameControllerProvider : Windows::Gaming::Input::Custom::IGipGameControllerProvider
    {
        GipGameControllerProvider(std::nullptr_t) noexcept {}
        GipGameControllerProvider(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Gaming::Input::Custom::IGipGameControllerProvider(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) HidGameControllerProvider : Windows::Gaming::Input::Custom::IHidGameControllerProvider
    {
        HidGameControllerProvider(std::nullptr_t) noexcept {}
        HidGameControllerProvider(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Gaming::Input::Custom::IHidGameControllerProvider(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) XusbGameControllerProvider : Windows::Gaming::Input::Custom::IXusbGameControllerProvider
    {
        XusbGameControllerProvider(std::nullptr_t) noexcept {}
        XusbGameControllerProvider(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Gaming::Input::Custom::IXusbGameControllerProvider(ptr, take_ownership_from_abi) {}
    };
}
#endif
