#include "ColliderComponent.h"
#include "../../GameObject/GameObject.h"

using namespace SuperGameEngine;

ColliderComponent::ColliderComponent() : GameComponent(), Collider()
{
}

ColliderComponent::~ColliderComponent()
{
}

GameObject* ColliderComponent::GetParentObject()
{
    return GameComponent::GetParent();
}
