#include "EnumFilterFactory.h"

using namespace FatedQuestLibraries;

void EnumFilterFactory::RegisterValues(
    const std::string& type,
    const std::vector<std::string>& values)
{
    GetMap().insert_or_assign(type, values);

    std::unordered_set<std::string> setOfStrings;
    setOfStrings.reserve(values.size());
    setOfStrings.insert(values.begin(), values.end());
    GetSetMap().insert_or_assign(type, setOfStrings);
}

std::vector<std::string> EnumFilterFactory::GetValues(const std::string& type)
{
    auto it = GetMap().find(type);
    if (it != GetMap().end())
    {
        return it->second;
    }

    return {};
}

std::unordered_set<std::string> EnumFilterFactory::GetValuesAsSet(const std::string& type)
{
    auto it = GetSetMap().find(type);
    if (it != GetSetMap().end())
    {
        return it->second;
    }

    return {};
}
