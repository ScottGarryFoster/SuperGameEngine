#include "StringHelpers.h"

using namespace StandardCLibrary;

std::string StringHelpers::Join(const std::string& separator, const std::vector<std::string>& list)
{
    if (list.empty())
    {
        return std::string();
    }

    std::string finalString = list[0];
    for (size_t i = 1; i < list.size(); ++i)
    {
        finalString += separator + list[i];
    }

    return finalString;
}

std::vector<std::string> StringHelpers::Split(const std::string& separator, const std::string& input)
{
    std::vector<std::string> newList;

    size_t start = 0, end = 0;
    while ((end = input.find(separator, start)) != std::string::npos)
    {
        newList.push_back(input.substr(start, end - start));
        start = end + separator.length();
    }
    newList.push_back(input.substr(start));

    return newList;
}

std::string StringHelpers::Trim(const std::string& input)
{
    if (input.empty())
    {
        return std::string();
    }

    size_t end = input.length();

    std::string copy = std::string();
    bool found = false;
    if (input[0] == ' ')
    {
        for (size_t i = 0; i < input.length(); ++i)
        {
            if (found)
            {
                copy += input[i];
            }
            else if (input[i] != ' ')
            {
                found = true;
                copy += input[i];
            }
        }
    }
    else
    {
        copy = input;
    }

    std::string returnn = std::string();
    if (copy[copy.length() - 1] == ' ')
    {
        for (size_t i = copy.length() - 1; i > 0; --i)
        {
            if (copy[i] != ' ')
            {
                end = i;
                break;
            }
        }

        for (size_t i = 0; i < end + 1; ++i)
        {
            returnn += copy[i];
        }
    }
    else
    {
        returnn = copy;
    }

    return returnn;
}

void StringHelpers::ConvertToLower(std::string& input)
{
    for (char& c : input)
    {
        if (c >= 'A' && c <= 'Z')
        {
            c = c - 'A' + 'a';
        }
    }
}

std::string StringHelpers::ToLower(const std::string& input)
{
    std::string output = input;
    ConvertToLower(output);
    return output;
}

void StringHelpers::ConvertToUpper(std::string& input)
{
    for (char& c : input)
    {
        if (c >= 'a' && c <= 'z')
        {
            c = c - 'a' + 'A';
        }
    }
}

std::string StringHelpers::ToUpper(const std::string& input)
{
    std::string output = input;
    ConvertToUpper(output);
    return output;
}

std::string StringHelpers::ConvertFrom(const std::vector<unsigned char>& input)
{
    std::string output = std::string();
    if (!input.empty())
    {
        std::string str(input.begin(), input.end());
        output = str;
    }

    return output;
}

bool StringHelpers::Equals(const std::string& left, const std::string& right, bool ignorecase)
{
    std::string compareLeft = left;
    std::string compareRight = right;
    if (ignorecase)
    {
        ConvertToLower(compareLeft);
        ConvertToLower(compareRight);
    }

    return compareLeft == compareRight;
}
