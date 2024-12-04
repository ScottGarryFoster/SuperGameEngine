#include "WindowsGUID.h"
#include <objbase.h>

using namespace FatedQuestLibraries;
WindowsGUID::WindowsGUID()
{
    Generate();
}

void WindowsGUID::Generate()
{
    HRESULT result = CoCreateGuid(&m_guid);
    m_asNumber = ToNumber(m_guid);
}

bool WindowsGUID::operator==(const Guid& other) const
{
    return ToString() == other.ToString();
}

void WindowsGUID::FromString(std::string value)
{
    int len = MultiByteToWideChar(CP_ACP, 0, value.c_str(), -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, value.c_str(), -1, wstr, len);
    LPCOLESTR oleStr = wstr;

    HRESULT hr = CLSIDFromString(oleStr, &m_guid);
    if (SUCCEEDED(hr))
    {
        m_asNumber = ToNumber(m_guid);
    }
}

std::string WindowsGUID::ToString() const
{
    wchar_t guidString[40];
    HRESULT result = StringFromGUID2(m_guid, guidString, 40);

    int len = WideCharToMultiByte(CP_UTF8, 0, guidString, -1, NULL, 0, NULL, NULL);
    char* narrowStr = new char[len];
    WideCharToMultiByte(CP_UTF8, 0, guidString, -1, narrowStr, len, NULL, NULL);

    return narrowStr;
}

uint64_t WindowsGUID::AsNumber() const
{
    // Pre-calculated number on set to help performance
    // This is called a lot during map/dictionaries.
    return m_asNumber;
}

uint64_t WindowsGUID::ToNumber(const GUID& guid)
{
    uint64_t number = 0;
    number += static_cast<uint64_t>(guid.Data1);
    number += static_cast<uint64_t>(guid.Data2) << 32;
    number += static_cast<uint64_t>(guid.Data3) << 48;

    for (int i = 0; i < 8; ++i)
    {
        number += static_cast<uint64_t>(guid.Data4[i]) << (i * 8);
    }

    return number;
}