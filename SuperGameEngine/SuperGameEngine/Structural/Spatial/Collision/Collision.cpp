#include "Collision.h"
#include "../../../Structural/GameObject/GameObject.h"
#include "../../../Structural/Components/Colliders/Collider.h"

using namespace SuperGameEngine;
Collision::Collision(GameObject* gameObject, Collider* collider)
{
    m_collider = collider;
    m_gameObject = gameObject;
}

GameObject* Collision::GetCollidedGameObject()
{
    return m_gameObject;
}

Collider* Collision::GetCollider()
{
    return m_collider;
}
