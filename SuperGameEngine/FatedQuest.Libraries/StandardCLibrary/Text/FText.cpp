#include "FText.h"
#include <sstream>
#include <string>
#include <vector>
#include <cstdarg>

#include <codecvt>
#include <locale>

#ifdef _WINDOWS
    #include <Windows.h>
#endif // _WINDOWS


using namespace StandardCLibrary;

FText::FText()
{
    m_storage = L"";
}

FText::FText(const std::vector<std::string> contents)
{
    std::stringstream content;
    for (std::string input : contents)
    {
        content << input;
    }

    m_storage = ConvertToWide(content.str());
}

FText::FText(const std::vector<std::wstring> contents)
{
    std::stringstream content;
    std::wstring output = L"";
    for (std::wstring input : contents)
    {
        output += input;
    }

    m_storage = output;
}

FText::FText(const std::wstring str1)
{
    m_storage = str1;
}

FText::FText(const std::wstring str1, const std::wstring str2)
{
    m_storage = str1 + str2;
}

FText::FText(const std::wstring str1, const std::wstring str2, const std::wstring str3)
{
    m_storage = str1 + str2 + str3;
}

FText::FText(const std::wstring str1, const std::wstring str2, const std::wstring str3, const std::wstring str4)
{
    m_storage = str1 + str2 + str3 + str4;
}

FText::FText(const std::wstring str1, const std::wstring str2, const std::wstring str3, const std::wstring str4, const std::wstring str5)
{
    m_storage = str1 + str2 + str3 + str4 + str5;
}

FText::FText(const std::wstring str1, const std::wstring str2, const std::wstring str3, const std::wstring str4, const std::wstring str5, const std::wstring str6)
{
    m_storage = str1 + str2 + str3 + str4 + str5 + str6;
}

FText::FText(const std::wstring str1, const std::wstring str2, const std::wstring str3, const std::wstring str4, const std::wstring str5, const std::wstring str6, const std::wstring str7)
{
    m_storage = str1 + str2 + str3 + str4 + str5 + str6 + str7;
}

FText::FText(const std::wstring str1, const std::wstring str2, const std::wstring str3, const std::wstring str4, const std::wstring str5, const std::wstring str6, const std::wstring str7, const std::wstring str8)
{
    m_storage = str1 + str2 + str3 + str4 + str5 + str6 + str7 + str8;
}

FText::FText(const std::wstring str1, const std::wstring str2, const std::wstring str3, const std::wstring str4, const std::wstring str5, const std::wstring str6, const std::wstring str7, const std::wstring str8, const std::wstring str9)
{
    m_storage = str1 + str2 + str3 + str4 + str5 + str6 + str7 + str8 + str9;
}

FText::FText(const std::wstring str1, const std::wstring str2, const std::wstring str3, const std::wstring str4, const std::wstring str5, const std::wstring str6, const std::wstring str7, const std::wstring str8, const std::wstring str9, const std::wstring str10)
{
    m_storage = str1 + str2 + str3 + str4 + str5 + str6 + str7 + str8 + str9 + str10;
}

FText::FText(const std::string str1)
{
    m_storage = ConvertToWide(str1);
}

FText::FText(const std::string str1, const std::string str2)
{
    std::stringstream content;
    content << str1 << str2;
    m_storage = ConvertToWide(content.str());
}

FText::FText(const std::string str1, const std::string str2, const std::string str3)
{
    std::stringstream content;
    content << str1 << str2 << str3;
    m_storage = ConvertToWide(content.str());
}

FText::FText(const std::string str1, const std::string str2, const std::string str3, const std::string str4)
{
    std::stringstream content;
    content << str1 << str2 << str3 << str4;
    m_storage = ConvertToWide(content.str());
}

FText::FText(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5)
{
    std::stringstream content;
    content << str1 << str2 << str3 << str4 << str5;
    m_storage = ConvertToWide(content.str());
}

FText::FText(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
    const std::string str6)
{
    std::stringstream content;
    content << str1 << str2 << str3 << str4 << str5 << str6;
    m_storage = ConvertToWide(content.str());
}

FText::FText(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
    const std::string str6, const std::string str7)
{
    std::stringstream content;
    content << str1 << str2 << str3 << str4 << str5 << str6 << str7;
    m_storage = ConvertToWide(content.str());
}

FText::FText(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
    const std::string str6, const std::string str7, const std::string str8)
{
    std::stringstream content;
    content << str1 << str2 << str3 << str4 << str5 << str6 << str7 << str8;
    m_storage = ConvertToWide(content.str());
}

FText::FText(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
    const std::string str6, const std::string str7, const std::string str8, const std::string str9)
{
    std::stringstream content;
    content << str1 << str2 << str3 << str4 << str5 << str6 << str7 << str8 << str9;
    m_storage = ConvertToWide(content.str());
}

FText::FText(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
    const std::string str6, const std::string str7, const std::string str8, const std::string str9, const std::string str10)
{
    std::stringstream content;
    content << str1 << str2 << str3 << str4 << str5 << str6 << str7 << str8 << str9 << str10;
    m_storage = ConvertToWide(content.str());
}

const std::string FText::AsStdString() const
{
    std::string value = ConvertFromWide(m_storage);
    return value;
}

const wchar_t* FText::AsCharArr() const
{
    return m_storage.c_str();
}

const std::wstring StandardCLibrary::FText::AsStdWstring() const
{
    return m_storage;
}

FText FText::operator+(const std::wstring& str) const
{
    std::wstring output = m_storage + str;
    return FText(output);
}

FText FText::operator+(const std::string& str) const
{
    std::wstring value = ConvertToWide(str);
    return FText(m_storage + value);
}

FText FText::operator+(const FText& str) const
{
    return FText(m_storage + str.m_storage);
}

FText FText::operator+(const float str) const
{
    std::wstring value = ConvertToWide(std::to_string(str));
    return FText(m_storage + value);
}

FText& FText::operator+=(const std::wstring& str)
{
    m_storage += str;
    return *this;
}

FText& FText::operator+=(const std::string& str)
{
    m_storage += ConvertToWide(str.c_str());
    return *this;
}

FText& FText::operator+=(const FText& str)
{
    m_storage += str.m_storage;
    return *this;
}

FText& FText::operator+=(const int str)
{
    m_storage += ConvertToWide(std::to_string(str));
    return *this;
}

FText& FText::operator+=(const long int str)
{
    m_storage += ConvertToWide(std::to_string(str));
    return *this;
}

FText& FText::operator+=(const unsigned long int str)
{
    m_storage += ConvertToWide(std::to_string(str));
    return *this;
}

FText& FText::operator+=(const double str)
{
    m_storage += ConvertToWide(std::to_string(str));
    return *this;
}

FText& FText::operator+=(const float str)
{
    m_storage += ConvertToWide(std::to_string(str));
    return *this;
}

FText FText::operator+(const double str) const
{
    return FText(m_storage + ConvertToWide(std::to_string(str)));
}

FText FText::operator+(const int str) const
{
    return FText(m_storage + ConvertToWide(std::to_string(str)));
}

FText FText::operator+(const long int str) const
{
    return FText(m_storage + ConvertToWide(std::to_string(str)));
}

FText FText::operator+(const unsigned long int str) const
{
    return FText(m_storage + ConvertToWide(std::to_string(str)));
}

bool FText::operator==(const std::wstring& other) const
{
    return m_storage == other;
}

bool FText::operator==(const std::string& other) const
{
    return m_storage == ConvertToWide(other);
}

bool FText::operator==(const FText& other) const
{
    return m_storage == other.m_storage;
}

FText FText::ToLower() const
{
    std::locale locale;
    std::wstring output;
    output.resize(m_storage.size());

    for (size_t i = 0; i < m_storage.size(); ++i)
    {
        output[i] = std::tolower(m_storage[i], locale);
    }

    return FText(output);
}

void FText::ConvertToLower()
{
    std::locale locale;
    std::wstring output;
    output.resize(m_storage.size());

    for (size_t i = 0; i < m_storage.size(); ++i)
    {
        m_storage[i] = std::tolower(m_storage[i], locale);
    }
}

FText FText::ToUpper() const
{
    std::locale locale;
    std::wstring output;
    output.resize(m_storage.size());

    for (size_t i = 0; i < m_storage.size(); ++i)
    {
        output[i] = std::toupper(m_storage[i], locale);
    }

    return FText(output);
}


void FText::ConvertToUpper()
{
    std::locale locale;
    std::wstring output;
    output.resize(m_storage.size());

    for (size_t i = 0; i < m_storage.size(); ++i)
    {
        m_storage[i] = std::toupper(m_storage[i], locale);
    }
}

bool StandardCLibrary::FText::IsEmptyOrWhitespace() const
{
    std::string empty;
    for (const char& c : m_storage)
    {
        if (c != ' ')
        {
            empty += c;
        }
    }

    return empty.length() == 0;
}

std::vector<FText> FText::Split(FText& toSplit, FText by)
{
    std::wstring toSplitAsString = toSplit.m_storage;
    std::wstring splitByAsString = by.m_storage;
    std::vector<FText> newList;

    size_t start = 0, end = 0;
    while ((end = toSplitAsString.find(splitByAsString, start)) != std::wstring::npos)
    {
        newList.push_back(
            FText(toSplitAsString.substr(start, end - start))
        );
        start = end + splitByAsString.length();
    }
    newList.push_back(toSplitAsString.substr(start));

    return newList;
}

std::vector<std::string> FText::Split(std::string& toSplit, std::string by)
{
    std::vector<std::string> newList;

    size_t start = 0, end = 0;
    while ((end = toSplit.find(by, start)) != std::string::npos)
    {
        newList.push_back(toSplit.substr(start, end - start));
        start = end + by.length();
    }
    newList.push_back(toSplit.substr(start));

    return newList;
}

// This method is deprecated and we should use the newer method for Windows with
// defines. So long as it converts back and forth it should be fine.
// Tests should ensure this is safe.
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
std::wstring FText::ConvertToWide(const std::string value) const
{
//#ifdef _WINDOWS
//    int count = MultiByteToWideChar(CP_UTF8, 0, value.c_str(), -1, nullptr, 0);
//    std::wstring wide(count, 0);
//    MultiByteToWideChar(CP_UTF8, 0, value.c_str(), -1, &wide[0], count);
//    return wide;
//#else
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(value);
//#endif // _WINDOWS
}

std::string FText::ConvertFromWide(const std::wstring value) const
{
//#ifdef _WINDOWS
//    int count = WideCharToMultiByte(CP_UTF8, 0, value.c_str(), -1, nullptr, 0, nullptr, nullptr);
//    std::string narrow(count, 0);
//    WideCharToMultiByte(CP_UTF8, 0, value.c_str(), -1, &narrow[0], count, nullptr, nullptr);
//    return narrow;
//#else
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(value);
//#endif // _WINDOWS
}
