#include "VectorHelpers.h"

bool FatedQuestLibraries::VectorHelpers::ContainsString(
    const std::vector<std::string>& data,
    const std::string& lookFor)
{
    size_t lookForLength = lookFor.size();
    for (const std::string& entry : data)
    {
        if (entry.size() != lookForLength)
        {
            continue;
        }

        if (entry == lookFor)
        {
            return true;
        }
    }

    return false;
}
