#include "ComponentFactory.h"

using namespace SuperGameEngine;

void ComponentFactory::RegisterComponent(
    const std::string& type, 
    std::function<std::shared_ptr<GameComponent>()> constructor)
{
    GetMap()[type] = constructor;
}

std::shared_ptr<GameComponent> ComponentFactory::CreateComponent(const std::string& type)
{
    auto it = GetMap().find(type);
    if (it != GetMap().end())
    {
        return it->second();
    }

    return nullptr;
}
