#include "SceneToGameObjectPackage.h"

#include "../../Structural/Spatial/Collision/CollisionDectection.h"

using namespace SuperGameEngine;

SceneToGameObjectPackage::SceneToGameObjectPackage(CollisionDectectionSubscription* collisionDection)
{
    m_collisionDectection = collisionDection;
}

SceneToGameObjectPackage::~SceneToGameObjectPackage()
{
}

CollisionDectectionSubscription* SceneToGameObjectPackage::GetCollisionDectection()
{
    return m_collisionDectection;
}
