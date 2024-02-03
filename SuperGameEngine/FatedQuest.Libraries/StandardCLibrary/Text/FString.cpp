#include "FString.h"
#include <sstream>
#include <string>
#include <vector>
#include <cstdarg>

using namespace StandardCLibrary;

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