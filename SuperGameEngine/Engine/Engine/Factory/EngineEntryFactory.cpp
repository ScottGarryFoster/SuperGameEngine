#include "EngineEntryFactory.h"
#include "../../EngineEntry/EngineEntry.h"

using namespace SuperGameEngine;

void EngineEntryFactory::RegisterEngineEntry(
    const std::string& type,
    std::function<std::shared_ptr<EngineEntry>()> constructor)
{
    GetMap()[type] = constructor;
}

std::shared_ptr<EngineEntry> EngineEntryFactory::CreateEngineEntry(const std::string& type)
{
    auto it = GetMap().find(type);
    if (it != GetMap().end())
    {
        return it->second();
    }

    return nullptr;
}