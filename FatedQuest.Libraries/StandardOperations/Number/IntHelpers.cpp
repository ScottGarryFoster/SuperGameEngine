#include "IntHelpers.h"

#include <stdexcept>

using namespace FatedQuestLibraries;

bool IntHelpers::TryParse(const std::string& parsing, int& outValue)
{
    outValue = -1;
    try
    {
        outValue = std::stoi(parsing);
        return true;
    }
    catch (const std::exception e)
    {

    }

    return false;
}

bool IntHelpers::TryParse(const std::string& parsing, unsigned int& outValue)
{
    outValue = 0;
    try
    {
        outValue = std::stoul(parsing);
        return true;
    }
    catch (const std::exception e)
    {

    }

    return false;
}

int32_t IntHelpers::SafeAddition(int32_t left, int32_t right)
{
    if ((right > 0 && left > INT32_MAX - right) || 
        (right < 0 && left < INT32_MIN - right))
    {
        throw std::overflow_error("Integer addition overflow");
    }

    return left + right;
}
