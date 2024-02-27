#include "WindowsGUID.h"
#include <objbase.h>

using namespace StandardCLibrary;
WindowsGUID::WindowsGUID()
{
    Generate();
}

void WindowsGUID::Generate()
{
    HRESULT result = CoCreateGuid(&m_guid);
}

bool WindowsGUID::operator==(GUID& other) const
{
    return ToFString() == other.ToString();
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
        // Successfully converted string to GUID
        //std::cout << "Successfully converted string to GUID" << std::endl;
    }
    else
    {
        // Failed to convert string to GUID
        //std::cout << "Failed to convert string to GUID" << std::endl;
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

FString StandardCLibrary::WindowsGUID::ToFString() const
{
    return FString(ToString());
}
