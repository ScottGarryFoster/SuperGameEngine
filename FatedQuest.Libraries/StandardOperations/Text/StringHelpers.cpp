#include <algorithm>
#include "StringHelpers.h"

#include "CaseSensitivity.h"

using namespace FatedQuestLibraries;

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

std::vector<std::string> StringHelpers::Split(const std::string& toSplit, const std::string& by)
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

std::string StringHelpers::Trim(const std::string& input)
{
    if (input.empty())
    {
        return {};
    }

    auto start = 
        std::find_if_not(
        input.begin(), input.end(),
        [](unsigned char ch) { return std::isspace(ch); });

    // The string is all whitespace
    if (start == input.end())
    {
        return {};
    }

    auto end = 
        std::find_if_not(
        input.rbegin(), input.rend(),
        [](unsigned char ch) { return std::isspace(ch); }).base();

    return { start, end };
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

std::string StringHelpers::ReplaceAll(const std::string& input, const std::string& find, const std::string& replace)
{
    if (input.empty())
    {
        return {};
    }

    std::string returnString = input;
    size_t startPos = 0;
    while ((startPos = returnString.find(find, startPos)) != std::string::npos)
    {
        returnString.replace(startPos, find.length(), replace);

        // Ensure to move the pointer but also ensure to not move it too much in-case
        // you are replacing something shorter than you are finding it or replacing single
        // characters.
        startPos += replace.length();
        if (replace.length() < find.length())
        {
            startPos -= (find.length() - replace.length());
        }
    }

    return returnString;
}

std::string StringHelpers::Capitalize(const std::string& input)
{
    if (input.empty())
    {
        return input;
    }

    std::string answer = "";
    std::vector<std::string> sentences = StringHelpers::Split(input, ".");
    for (std::string& sentence : sentences)
    {
        if (sentence.empty())
        {
            continue;
        }

        if (sentence[0] >= 'a' && sentence[0] <= 'z')
        {
            sentence[0] = sentence[0] - 'a' + 'A';
        }

        answer += sentence;
    }

    return answer;
}

bool StringHelpers::Contains(const std::string& toFind, const std::string& inText)
{
    if (toFind.empty() && inText.empty())
    {
        return true;
    }

    if (toFind.empty() || inText.empty())
    {
        return false;
    }

    return inText.find(toFind) != std::string::npos;
}

std::string StringHelpers::DisplayName(const std::string& input)
{
    auto addFillerCharacter = [](std::string& displayName, const char& character)
    {
        if (!displayName.empty() && displayName.back() != character)
        {
            displayName.push_back(character);
        }
    };

    std::string displayName;
    bool doCapital = false;
    for (char character : input)
    {
        if (character == '.')
        {
            doCapital = true;
            addFillerCharacter(displayName, '.');

        }
        else if (character == '_' || character == '-')
        {
            addFillerCharacter(displayName, ' ');
        }
        else
        {
            if (doCapital &&
                std::isalpha(static_cast<unsigned char>(character)))
            {
                character = std::toupper(static_cast<unsigned char>(character));
                doCapital = false;
            }

            if (std::isupper(static_cast<unsigned char>(character)))
            {
                addFillerCharacter(displayName, ' ');
            }

            displayName.push_back(character);
        }
    }

    return displayName;
}

bool StringHelpers::Equals(const std::string& left, const std::string& right, CaseSensitivity caseSensitivity)
{
    if (caseSensitivity == CaseSensitivity::IgnoreCase)
    {
        std::string newLeft = ToLower(left);
        std::string newRight = ToLower(right);
        return newLeft == newRight;
    }

    return left == right;
}