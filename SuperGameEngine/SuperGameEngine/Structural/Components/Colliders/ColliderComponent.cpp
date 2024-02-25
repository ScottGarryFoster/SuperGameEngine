#include "ColliderComponent.h"
#include "../../GameObject/GameObject.h"

using namespace SuperGameEngine;

inline GameObject* ColliderComponent::GetParentObject()
{
    return GameComponent::GetParent();
}
