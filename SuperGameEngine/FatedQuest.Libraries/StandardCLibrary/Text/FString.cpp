#include "FString.h"
#include <sstream>
#include <string>
#include <vector>
#include <cstdarg>

using namespace StandardCLibrary;

FString::FString()
{
    m_storage = "";
}

FString::FString(const std::vector<std::string> contents)
{
    std::stringstream content;
    for (std::string input : contents)
    {
        content << input;
    }

    m_storage = content.str();
}

FString::FString(const std::string str1)
{
    m_storage = str1;
}

FString::FString(const std::string str1, const std::string str2)
{
    std::stringstream content;
    content << str1 << str2;
    m_storage = content.str();
}

FString::FString(const std::string str1, const std::string str2, const std::string str3)
{
    std::stringstream content;
    content << str1 << str2 << str3;
    m_storage = content.str();
}

FString::FString(const std::string str1, const std::string str2, const std::string str3, const std::string str4)
{
    std::stringstream content;
    content << str1 << str2 << str3 << str4;
    m_storage = content.str();
}

FString::FString(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5)
{
    std::stringstream content;
    content << str1 << str2 << str3 << str4 << str5;
    m_storage = content.str();
}

FString::FString(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
    const std::string str6)
{
    std::stringstream content;
    content << str1 << str2 << str3 << str4 << str5 << str6;
    m_storage = content.str();
}

FString::FString(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
    const std::string str6, const std::string str7)
{
    std::stringstream content;
    content << str1 << str2 << str3 << str4 << str5 << str6 << str7;
    m_storage = content.str();
}

FString::FString(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
    const std::string str6, const std::string str7, const std::string str8)
{
    std::stringstream content;
    content << str1 << str2 << str3 << str4 << str5 << str6 << str7 << str8;
    m_storage = content.str();
}

FString::FString(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
    const std::string str6, const std::string str7, const std::string str8, const std::string str9)
{
    std::stringstream content;
    content << str1 << str2 << str3 << str4 << str5 << str6 << str7 << str8 << str9;
    m_storage = content.str();
}

FString::FString(const std::string str1, const std::string str2, const std::string str3, const std::string str4, const std::string str5,
    const std::string str6, const std::string str7, const std::string str8, const std::string str9, const std::string str10)
{
    std::stringstream content;
    content << str1 << str2 << str3 << str4 << str5 << str6 << str7 << str8 << str9 << str10;
    m_storage = content.str();
}

const std::string FString::AsStdString()
{
    return m_storage;
}

const char* FString::AsCharArr()
{
    return m_storage.c_str();
}

FString FString::operator+(const std::string& str) const
{
    return FString(m_storage.c_str(), str.c_str());
}

FString FString::operator+(const FString& str) const
{
    return FString(m_storage.c_str(), str.m_storage.c_str());
}

FString FString::operator+(const int str) const
{
    return FString(std::to_string(str));
}

FString FString::operator+(const long int str) const
{
    return FString(std::to_string(str));
}

FString FString::operator+(const unsigned long int str) const
{
    return FString(std::to_string(str));
}

bool FString::operator==(const std::string& other) const
{
    return m_storage.compare(other);
}

bool FString::operator==(const FString& other) const
{
    return m_storage.compare(other.m_storage);
}

FString FString::ToLower()
{
    std::string toLower = m_storage.c_str();
    for (char& c : toLower)
    {
        if (c >= 'A' && c <= 'Z')
        {
            c = c - 'A' + 'a';
        }
    }

    return FString(toLower);
}

void FString::ConvertToLower()
{
    for (char& c : m_storage)
    {
        if (c >= 'A' && c <= 'Z')
        {
            c = c - 'A' + 'a';
        }
    }
}

FString FString::ToUpper()
{
    std::string toUpper = m_storage.c_str();
    for (char& c : toUpper)
    {
        if (c >= 'a' && c <= 'z')
        {
            c = c - 'a' + 'A';
        }
    }

    return FString(toUpper);
}


void FString::ConvertToUpper()
{
    for (char& c : m_storage)
    {
        if (c >= 'a' && c <= 'z')
        {
            c = c - 'a' + 'A';
        }
    }
}