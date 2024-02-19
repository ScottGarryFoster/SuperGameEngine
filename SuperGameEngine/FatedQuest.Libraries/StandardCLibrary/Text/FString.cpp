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

const std::string FString::AsStdString() const
{
    return m_storage;
}

const char* FString::AsCharArr() const
{
    return m_storage.c_str();
}

FString FString::operator+(const std::string& str) const
{
    return FString(m_storage + str.c_str());
}

FString FString::operator+(const FString& str) const
{
    return FString(m_storage + str.m_storage);
}

FString FString::operator+(const float str) const
{
    return FString(m_storage.c_str() + std::to_string(str));
}

FString& FString::operator+=(const std::string& str)
{
    m_storage += str.c_str();
    return *this;
}

FString& FString::operator+=(const FString& str)
{
    m_storage += str.m_storage;
    return *this;
}

FString& FString::operator+=(const int str)
{
    m_storage += std::to_string(str);
    return *this;
}

FString& FString::operator+=(const long int str)
{
    m_storage += std::to_string(str);
    return *this;
}

FString& FString::operator+=(const unsigned long int str)
{
    m_storage += std::to_string(str);
    return *this;
}

FString& FString::operator+=(const double str)
{
    m_storage += std::to_string(str);
    return *this;
}

FString& FString::operator+=(const float str)
{
    m_storage += std::to_string(str);
    return *this;
}

FString FString::operator+(const double str) const
{
    return FString(m_storage.c_str() + std::to_string(str));
}

FString FString::operator+(const int str) const
{
    return FString(m_storage.c_str() + std::to_string(str));
}

FString FString::operator+(const long int str) const
{
    return FString(m_storage.c_str() + std::to_string(str));
}

FString FString::operator+(const unsigned long int str) const
{
    return FString(m_storage.c_str() + std::to_string(str));
}

bool FString::operator==(const std::string& other) const
{
    return m_storage == other;
}

bool FString::operator==(const FString& other) const
{
    return m_storage == other.m_storage;
}

FString FString::ToLower() const
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

FString FString::ToUpper() const
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

bool StandardCLibrary::FString::IsEmptyOrWhitespace() const
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

std::vector<FString> FString::Split(FString& toSplit, FString by)
{
    std::string toSplitAsString = toSplit.AsStdString();
    std::string splitByAsString = by.AsStdString();
    std::vector<FString> newList;

    size_t start = 0, end = 0;
    while ((end = toSplitAsString.find(splitByAsString, start)) != std::string::npos)
    {
        newList.push_back(
            FString(toSplitAsString.substr(start, end - start))
        );
        start = end + splitByAsString.length();
    }
    newList.push_back(toSplitAsString.substr(start));

    return newList;
}

std::vector<std::string> FString::Split(std::string& toSplit, std::string by)
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