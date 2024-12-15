#include "StringAdvancedReplace.h"

using namespace FatedQuestLibraries;

std::string StringAdvancedReplace::Replace(
    const std::string& source,
    const std::string& criteria,
    const std::string& replacement)
{
    std::string result = source;
    size_t pos = 0;
    while ((pos = result.find(criteria, pos)) != std::string::npos)
    {
        result.replace(pos, criteria.length(), replacement);
        pos += replacement.length();
    }

    return result;
}

void StringAdvancedReplace::ReplaceInPlace(
    std::string& source, 
    const std::string& criteria, 
    const std::string& replacement)
{
    size_t pos = 0;
    while ((pos = source.find(criteria, pos)) != std::string::npos)
    {
        source.replace(pos, criteria.length(), replacement);
        pos += replacement.length();
    }
}
