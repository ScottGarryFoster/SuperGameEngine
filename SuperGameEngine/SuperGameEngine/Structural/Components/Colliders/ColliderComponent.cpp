#include "ColliderComponent.h"
#include "../../GameObject/GameObject.h"

using namespace SuperGameEngine;

GameObject* ColliderComponent::GetParentObject()
{
    return GameComponent::GetParent();
}
