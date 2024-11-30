#include "IntHelpers.h"

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
