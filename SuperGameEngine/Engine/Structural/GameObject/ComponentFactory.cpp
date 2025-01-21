#include "ComponentFactory.h"
#include "../Component/GameComponent.h"
#include <algorithm>
#include <iterator>

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

std::vector<std::string> ComponentFactory::GetAllComponentTypes()
{
    auto it = GetMap();
    std::vector<std::string> allTypes;
    allTypes.reserve(GetMap().size());

    std::ranges::transform(it, std::back_inserter(allTypes),
                           [](const auto& pair) { return pair.first; });

    return allTypes;
}
