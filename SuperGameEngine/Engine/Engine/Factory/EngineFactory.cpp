#include "EngineFactory.h"
#include "../../EngineEntry/Engine.h"

using namespace SuperGameEngine;

void EngineFactory::RegisterEngine(
    const std::string& type,
    const std::function<std::shared_ptr<Engine>()>& constructor)
{
    GetMap()[type] = constructor;
}

std::shared_ptr<Engine> EngineFactory::CreateEngine(const std::string& type)
{
    auto it = GetMap().find(type);
    if (it != GetMap().end())
    {
        return it->second();
    }

    return nullptr;
}